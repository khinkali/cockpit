module Security.Env exposing (Model, init, reqEnv)

import Http
import Json.Decode as Decode
import Url
import Url.Parser as Parser exposing (..)



{- Read Keycloak configuration file from server -}


type alias Model =
    String


init : Model
init =
    ""



--- Request for Keycloak enviroment url ---


reqEnv : (Result Http.Error String -> msg) -> Cmd msg
reqEnv msg =
    Http.get
        { url = "/config/config.json"
        , expect = Http.expectJson msg (Decode.field "env" (Decode.field "url" Decode.string))
        }
