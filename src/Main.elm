module Main exposing (Model, Msg(..), init, main, update, view)

import API.Keycloak as Keycloak exposing (..)
import API.Env as Env exposing (..)
import Browser
import Browser.Navigation as Nav
import Home.Page as HomePage
import Html exposing (..)
import Html.Attributes exposing (..)
import Json.Decode as Decode
import NotFound.Page as NotFoundPage
import Url.Parser as Parser exposing (..)
import Url
import Http
import Account.Page as AccountPage
import Menu.Page as MenuPage



---- MODEL ----

type Page
    = NotFoundPage NotFoundPage.Model
    | HomePage HomePage.Model
    | AccountPage AccountPage.Model


type alias Model =
    { key : Nav.Key
    , url : Url.Url
    , auth : Keycloak.Struct
    , page : Page
    , env : Env.Model
    }


init : Decode.Value -> Url.Url -> Nav.Key -> ( Model, Cmd Msg )
init flags url key =
    case Keycloak.validate flags of
        Ok auth ->
            (Model key url auth (HomePage "Hello Foo") "", Cmd.map Env Env.send)
    
        Err err ->
            (Model key url (Keycloak.Struct "" "") (NotFoundPage "Keycloak provide wrong value") "", Cmd.none)


---- UPDATE ----


type Msg
    = LinkClicked Browser.UrlRequest
    | UrlChanged Url.Url
    | Env Env.Msg
    | NotFoundMsg NotFoundPage.Msg
    | HomeMsg HomePage.Msg
    | AccountMsg AccountPage.Msg
    | MenuMsg MenuPage.Msg


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
        AccountMsg accountMsg ->
            case model.page of
                AccountPage accountModel ->
                    navToAccount model (AccountPage.update accountMsg accountModel)
                _ -> 
                   (model, Cmd.none) 
        Env envMsg ->
            case Env.read envMsg of
                Ok value ->
                    navigate model.url { model | env = value }
                Err err ->
                    navToNotFound model (NotFoundPage.init "Missing enviroment")
        MenuMsg menuMsg ->
            (model, Cmd.none)  


--- NAVIGATION ---
navToHome : Model -> (HomePage.Model, Cmd HomePage.Msg) -> (Model, Cmd Msg)
navToHome model (homeModel, homeMsg) =
    ({model | page = HomePage homeModel},
     Cmd.map HomeMsg homeMsg )

navToAccount : Model -> (AccountPage.Model, Cmd AccountPage.Msg) -> (Model, Cmd Msg)
navToAccount model (accountModel, accountMsg) =
    ({model | page = AccountPage accountModel},
     Cmd.map AccountMsg accountMsg )

navToNotFound : Model -> (NotFoundPage.Model, Cmd NotFoundPage.Msg) -> (Model, Cmd Msg)
navToNotFound model (notFoundModel, notFoundMsg) =
    ({model | page = NotFoundPage notFoundModel},
     Cmd.map NotFoundMsg notFoundMsg )


navigate : Url.Url -> Model -> (Model, Cmd Msg)
navigate url model = 
    let
        parser = 
            oneOf [
                route top ( navToHome model HomePage.init),
                route (Parser.s "account") (navToAccount model (AccountPage.init model.env model.auth))
            ]
    in
    case Parser.parse parser url of
        Just page ->
            page
        Nothing -> 
            navToNotFound model (NotFoundPage.init "Can not find the page")


route : Parser a b -> a -> Parser (b -> c) c
route parser handler =
    Parser.map handler parser

--- SUBSCRIPTIONS ---


subscriptions : Model -> Sub Msg
subscriptions _ =
    Sub.none



---- VIEW ----

content : Model -> Html Msg
content model =
    main_ []
        [ case model.page of
            HomePage homeModel ->
                Html.map HomeMsg (HomePage.view homeModel)
            AccountPage accountModel ->    
                Html.map AccountMsg (AccountPage.view accountModel)
            NotFoundPage notFoundModel ->
                Html.map NotFoundMsg (NotFoundPage.view notFoundModel)
        ]


body : Model -> List (Html Msg)
body model =
    [ Html.map MenuMsg MenuPage.content
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
        , onUrlChange = UrlChanged
        , onUrlRequest = LinkClicked
        }
