module Home.Page exposing (Model, Msg(..), init, update, view)

import Html exposing (..)
import Html.Attributes exposing (..)



---- MODEL ----


type alias Model =
    String


init : ( Model, Cmd Msg )
init =
    ( "", Cmd.none )



---- UPDATE ----


type Msg
    = GotMsg String


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        GotMsg str ->
            ( str, Cmd.none )



-- SUBSCRIPTIONS
---- VIEW ----


view : Model -> Html Msg
view model =
    p [] [ text model ]
