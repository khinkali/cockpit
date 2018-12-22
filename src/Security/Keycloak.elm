module Security.Keycloak exposing (Model, Token, init, validate)

import Json.Decode exposing (..)


type alias Token =
    Result String Model


type alias Model =
    { subject : String
    , token : String
    }


init : Model
init =
    Model "" ""


subjectDecoder : Decoder String
subjectDecoder =
    field "subject" string


tokenDecoder : Decoder String
tokenDecoder =
    field "token" string


decodeModel : Decoder Model
decodeModel =
    map2 Model subjectDecoder tokenDecoder


validate : Value -> Token
validate flags =
    case decodeValue decodeModel flags of
        Ok value ->
            validateValue value

        Err err ->
            case err of
                Field field _ ->
                    Err field

                Index int _ ->
                    Err ("Index error " ++ String.fromInt int)

                OneOf _ ->
                    Err "One"

                Failure field _ ->
                    Err field



-- Configure, if the value is empty or not


validateValue : Model -> Result String Model
validateValue value =
    if value.subject == "" || value.token == "" then
        Err "Identification keys are empty."

    else
        Ok value
