module API.Keycloak exposing (Struct, Token, validate)

import Json.Decode exposing (..)


type alias Token =
    Result String Struct


type alias Struct =
    { subject : String
    , token : String
    }


subjectDecoder : Decoder String
subjectDecoder =
    field "subject" string


tokenDecoder : Decoder String
tokenDecoder =
    field "token" string


structDecoder : Decoder Struct
structDecoder =
    map2 Struct subjectDecoder tokenDecoder


validate : Value -> Token
validate flags =
    case decodeValue structDecoder flags of
        Ok value ->
            preventEmptyValue value

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


preventEmptyValue : Struct -> Result String Struct
preventEmptyValue value =
    if value.subject == "" || value.token == "" then
        Err "Identification keys are empty."

    else
        Ok value
