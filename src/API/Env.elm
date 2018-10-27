module API.Env exposing (send, Model, Msg, read)

import Json.Decode as Decode
import Url.Parser as Parser exposing (..)
import Url
import Http


--- Keycloak environment url for communication ---
type alias Model = String

---- UPDATE ----
type Msg = KcEnv (Result Http.Error Model)

    
--- Request for Keycloak enviroment url ---
reqKcEnv : Http.Request String
reqKcEnv = Http.get "/config/config.json" (Decode.field "env" (Decode.field "url" Decode.string))

send : Cmd Msg
send = Http.send KcEnv reqKcEnv

read : Msg -> (Result Http.Error Model)
read msg = 
    case msg of
        KcEnv resp ->
            resp