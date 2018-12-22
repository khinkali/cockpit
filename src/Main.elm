module Main exposing (Model, Msg(..), init, main, update, view)

import Account.Page as AccountPage
import Browser
import Browser.Navigation as Nav
import Error.Page as Error
import Home.Page as Home
import Html exposing (..)
import Html.Attributes exposing (..)
import Http
import Json.Decode as Decode
import Menu.Page as Menu
import NotFound.Page as NotFound
import Security.Data as Security
import Security.Keycloak as Keycloak
import Url
import Url.Parser as Parser exposing (..)



---- MODEL ----


type Page
    = NotFoundPage NotFound.Model
    | HomePage Home.Model
    | AccountPage AccountPage.Model


type alias Model =
    { url : Url.Url
    , key : Nav.Key
    , sec : Security.Model
    , page : Page
    }


init : Decode.Value -> Url.Url -> Nav.Key -> ( Model, Cmd Msg )
init flags url key =
    ( Model url key Security.init (HomePage "Hello Foo"), Cmd.none )



---- UPDATE ----


type PageMsg
    = NotFoundMsg NotFound.Msg
    | HomeMsg Home.Msg
    | AccountMsg AccountPage.Msg
    | MenuMsg Menu.Msg


type Msg
    = OnUrlChange Url.Url
    | OnUrlRequest Browser.UrlRequest
    | OnSecurity Security.Msg
    | OnPage PageMsg


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        OnUrlRequest urlRequest ->
            case urlRequest of
                Browser.Internal url ->
                    ( model, Nav.pushUrl model.key (Url.toString url) )

                Browser.External href ->
                    ( model, Nav.load href )

        OnUrlChange url ->
            navigate url model

        OnSecurity secMsg ->
            handleSecurity model (Security.update secMsg model.sec)

        OnPage pageMsg ->
            case pageMsg of
                HomeMsg homeMsg ->
                    case model.page of
                        HomePage homeModel ->
                            navToHome model (Home.update homeMsg homeModel)

                        _ ->
                            ( model, Cmd.none )

                NotFoundMsg notFoundMsg ->
                    case model.page of
                        NotFoundPage notFoundModel ->
                            navToNotFound model (NotFound.update notFoundMsg notFoundModel)

                        _ ->
                            ( model, Cmd.none )

                AccountMsg accountMsg ->
                    case model.page of
                        AccountPage accountModel ->
                            navToAccount model (AccountPage.update accountMsg accountModel)

                        _ ->
                            ( model, Cmd.none )

                MenuMsg menuMsg ->
                    ( model, Cmd.none )



-- UPDATE HANDLERS --


handleSecurity : Model -> ( Security.Model, Cmd Security.Msg ) -> ( Model, Cmd Msg )
handleSecurity model ( secModel, secMsg ) =
    case secModel.status of
        Error.Success ->
            ( { model | sec = secModel }, Cmd.map OnSecurity secMsg )

        Error.Failed error ->
            ( { model | page = HomePage "Can not query security requirements." }, Cmd.none )



--- NAVIGATION ---


navToHome : Model -> ( Home.Model, Cmd Home.Msg ) -> ( Model, Cmd Msg )
navToHome model ( homeModel, homeMsg ) =
    ( { model | page = HomePage homeModel }
    , Cmd.map OnPage (Cmd.map HomeMsg homeMsg)
    )


navToAccount : Model -> ( AccountPage.Model, Cmd AccountPage.Msg ) -> ( Model, Cmd Msg )
navToAccount model ( accountModel, accountMsg ) =
    ( { model | page = AccountPage accountModel }
    , Cmd.map OnPage (Cmd.map AccountMsg accountMsg)
    )


navToNotFound : Model -> ( NotFound.Model, Cmd NotFound.Msg ) -> ( Model, Cmd Msg )
navToNotFound model ( notFoundModel, notFoundMsg ) =
    ( { model | page = NotFoundPage notFoundModel }
    , Cmd.map OnPage (Cmd.map NotFoundMsg notFoundMsg)
    )


navigate : Url.Url -> Model -> ( Model, Cmd Msg )
navigate url model =
    let
        parser =
            oneOf
                [ route top (navToHome model Home.init)
                , route (Parser.s "account") (navToAccount model (AccountPage.init model.sec))
                ]
    in
    case Parser.parse parser url of
        Just page ->
            page

        Nothing ->
            navToNotFound model (NotFound.init "Can not find the page")


route : Parser a b -> a -> Parser (b -> c) c
route parser handler =
    Parser.map handler parser



--- SUBSCRIPTIONS ---


subscriptions : Model -> Sub Msg
subscriptions _ =
    Sub.batch
        [ Sub.map OnSecurity (Security.onSubKc (\value -> Security.OnSubKc (Keycloak.validate value)))
        ]



---- VIEW ----


content : Model -> Html PageMsg
content model =
    main_ []
        [ case model.page of
            HomePage homeModel ->
                Html.map HomeMsg (Home.view homeModel)

            AccountPage accountModel ->
                Html.map AccountMsg (AccountPage.view accountModel)

            NotFoundPage notFoundModel ->
                Html.map NotFoundMsg (NotFound.view notFoundModel)
        ]


body : Model -> List (Html Msg)
body model =
    [ Html.map OnPage (Html.map MenuMsg Menu.content)
    , Html.map OnPage (content model)
    ]


view : Model -> Browser.Document Msg
view model =
    { title = "Cockpit"
    , body = body model
    }



---- FUNCTIONS ----
---- PROGRAM ----


main : Program Decode.Value Model Msg
main =
    Browser.application
        { init = init
        , view = view
        , update = update
        , subscriptions = subscriptions
        , onUrlChange = OnUrlChange
        , onUrlRequest = OnUrlRequest
        }
