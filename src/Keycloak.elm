module Keycloak exposing (Struct, transform)

import Json.Decode exposing (..)


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


transform : Value -> Result String Struct
transform flags =
    case decodeValue structDecoder flags of
        Ok value ->
            Ok value

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
