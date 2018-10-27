module NotFound.Page exposing (..)

import Html exposing (..)
import Html.Attributes exposing (..)




---- MODEL ----


type alias Model = String


init : String -> (Model, Cmd Msg)
init text = (text, Cmd.none)


---- UPDATE ----

type Msg
    = GotMsg String

update : Msg -> Model -> (Model, Cmd Msg)
update msg model = 
    case msg of
        GotMsg str ->
            (str, Cmd.none)
            

--- SUBSCRIPTIONS ---


---- VIEW ----
view : Model -> Html Msg
view model = 
    p [] [text model]
