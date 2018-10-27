module Account.Page exposing (Msg(..), update, view, Model, init)

import API.Keycloak as Keycloak exposing (..)
import API.Env as Env exposing (..)
import API.Coins as Coins exposing (..)
import Html exposing (..)
import Html.Attributes exposing (..)
import Http exposing (..)


---- MODEL ----

type alias Model =
    { 
        currencies : List String,
        error : String
    }


init : Env.Model -> Keycloak.Struct -> ( Model, Cmd Msg )
init env kc =
    ( Model [] "" 
    , Http.send Currencies (Coins.reqCoins env kc)
    )

---- UPDATE ----


type Msg
    = Currencies (Result Http.Error (List String))

update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        Currencies resp ->
            case resp of
                Ok value ->
                    ({model | currencies = value }, Cmd.none)
                Err _ ->
                    ({model | error = "Can not query coins currency" }, Cmd.none)



--- SUBSCRIPTIONS ---

subscriptions : Model -> Sub Msg
subscriptions model =
    Sub.none


---- VIEW ----


view : Model -> Html Msg
view model =
    p [] [text model.error]


---- FUNCTIONS ----
