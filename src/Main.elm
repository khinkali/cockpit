module Main exposing (Model, Msg(..), init, main, update, view)

import API.Keycloak as Keycloak exposing (..)
import Browser
import Browser.Navigation as Nav
import Home.Page as HomePage
import Html exposing (..)
import Html.Attributes exposing (..)
import Json.Decode as Decode
import NotFound.Page as NotFoundPage
import Url.Parser as Parser exposing (..)
import Url



---- MODEL ----


type Page
    = NotFoundPage NotFoundPage.Model
    | HomePage HomePage.Model

type alias Model =
    { key : Nav.Key
    , url : Url.Url
    , auth : Keycloak.Token
    , page : Page
    }


init : Decode.Value -> Url.Url -> Nav.Key -> ( Model, Cmd Msg )
init flags url key =
    ( Model key url (Keycloak.validate flags) (HomePage HomePage.initText), Cmd.none )


---- UPDATE ----


type Msg
    = LinkClicked Browser.UrlRequest
    | UrlChanged Url.Url
    | NotFoundMsg NotFoundPage.Msg
    | HomeMsg HomePage.Msg


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        LinkClicked urlRequest ->
            case urlRequest of
                Browser.Internal url ->
                    ( model, Nav.pushUrl model.key (Url.toString url) )

                Browser.External href ->
                    ( model, Nav.load href )

        UrlChanged url ->
            navigate url model

        HomeMsg homeMsg ->
            case model.page of 
                HomePage homeModel ->
                    navToHome model (HomePage.update homeMsg homeModel)
                _ ->
                    (model, Cmd.none)

        NotFoundMsg notFoundMsg ->
            case model.page of 
                NotFoundPage notFoundModel ->
                    navToNotFound model (NotFoundPage.update notFoundMsg notFoundModel)
                _ ->
                    (model, Cmd.none)


--- NAVIGATION ---
navToHome : Model -> (HomePage.Model, Cmd HomePage.Msg) -> (Model, Cmd Msg)
navToHome model (homeModel, homeMsg) =
    ({model | page = HomePage homeModel},
     Cmd.map HomeMsg homeMsg )

navToNotFound : Model -> (NotFoundPage.Model, Cmd NotFoundPage.Msg) -> (Model, Cmd Msg)
navToNotFound model (notFoundModel, notFoundMsg) =
    ({model | page = NotFoundPage notFoundModel},
     Cmd.map NotFoundMsg notFoundMsg )




navigate : Url.Url -> Model -> (Model, Cmd Msg)
navigate url model = 
    let
        parser = 
            oneOf [
                route top ( navToHome model HomePage.init)
            ]
    in
    case Parser.parse parser url of
        Just page ->
            page
        _ -> 
            ({model | page = NotFoundPage "Can not find the page."},
            Cmd.none)


route : Parser a b -> a -> Parser (b -> c) c
route parser handler =
    Parser.map handler parser

--- SUBSCRIPTIONS ---


subscriptions : Model -> Sub Msg
subscriptions _ =
    Sub.none



---- VIEW ----


info : Html Msg
info =
    header [] [ text "Header" ]


createLink : String -> String -> Html Msg
createLink aPath aText =
    a [ href ("/" ++ aPath) ] [ text aText ]


navigation : Html Msg
navigation =
    ul []
        [ li [] [ createLink "" "home" ]
        , li [] [ createLink "account" "account" ]
        ]


content : Model -> Html Msg
content model =
    main_ []
        [ case model.page of
            HomePage homeModel ->
                Html.map HomeMsg (HomePage.view homeModel)
        
            NotFoundPage notFoundModel ->
                Html.map NotFoundMsg (NotFoundPage.view notFoundModel)
                
        ]


body : Model -> List (Html Msg)
body model =
    [ info
    , navigation
    , content model
    ]


view : Model -> Browser.Document Msg
view model =
    { title = "Cockpit"
    , body = body model
    }



---- PROGRAM ----


main : Program Decode.Value Model Msg
main =
    Browser.application
        { init = init
        , view = view
        , update = update
        , subscriptions = subscriptions
        , onUrlChange = UrlChanged
        , onUrlRequest = LinkClicked
        }
