module Error.Page exposing (Model, Status(..), createFailure, view)

import Html exposing (..)


type Status
    = Success
    | Failed String


type alias Model =
    Status


view : Model -> Html msg
view model =
    case model of
        Success ->
            span [] []

        Failed msg ->
            p [] [ text msg ]


createFailure : String -> Status
createFailure model =
    Failed model
