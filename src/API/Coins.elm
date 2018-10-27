module API.Coins exposing (reqCoins)

import API.Keycloak as Keycloak exposing (..)
import API.Env as Env exposing (..)
import Http exposing (..)
import Json.Decode as Decode

reqCoins : Env.Model -> Keycloak.Struct -> Request (List String)
reqCoins env kc = Http.request
    { method = "GET"
    , headers = [reqAuthHeader kc]
    , url = buildUrl env
    , body = Http.emptyBody
    , expect = Http.expectJson (Decode.list Decode.string)
    , timeout = Nothing
    , withCredentials = True
    }

reqAuthHeader : Keycloak.Struct -> Http.Header
reqAuthHeader kc = Http.header "Authorization" ("Bearer " ++ kc.token)


buildUrl : Env.Model -> String
buildUrl env = 
    env ++ "/sink/resources/coins"