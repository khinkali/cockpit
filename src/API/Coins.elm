module API.Coins exposing (reqCoins, reqUserCoins, reqAddCoin, UserCoin, UserCoins)

import API.Keycloak as Keycloak exposing (..)
import API.Env as Env exposing (..)
import Http exposing (..)
import Json.Decode as Decode
import Json.Encode as Encode

type alias UserCoin =
    {
        amount : Float,
        curr : String
    }

type alias UserCoins = List UserCoin

reqCoins : Env.Model -> Keycloak.Struct -> Request (List String)
reqCoins env kc = Http.request
    { method = "GET"
    , headers = [reqAuthHeader kc]
    , url = buildUrlCurrs env
    , body = Http.emptyBody
    , expect = Http.expectJson (Decode.list Decode.string)
    , timeout = Nothing
    , withCredentials = True
    }

reqAuthHeader : Keycloak.Struct -> Http.Header
reqAuthHeader kc = Http.header "Authorization" ("Bearer " ++ kc.token)


-- Url for query coin currencies
buildUrlCurrs : Env.Model -> String
buildUrlCurrs env = 
    env ++ "/sink/resources/coins"

-- Get all user coins
reqUserCoins :  Env.Model -> Keycloak.Struct -> Request UserCoins
reqUserCoins env kc = 
    Http.request
    { method = "GET"
    , headers = [reqAuthHeader kc]
    , url = buildUrlUserCoins env kc
    , body = Http.emptyBody
    , expect = Http.expectJson (userCoinsDecoder)
    , timeout = Nothing
    , withCredentials = True
    }

buildUrlUserCoins : Env.Model -> Keycloak.Struct -> String
buildUrlUserCoins env kc =
    env ++ "/sink/resources/users/" ++ kc.subject ++ "/coins"


amountDecoder : Decode.Decoder Float
amountDecoder =
    Decode.field "amount" Decode.float

currencyDecoder : Decode.Decoder String
currencyDecoder =
    Decode.field "coinSymbol" Decode.string

userCoinDecoder : Decode.Decoder UserCoin
userCoinDecoder = 
    Decode.map2 UserCoin amountDecoder currencyDecoder

userCoinsDecoder : Decode.Decoder UserCoins
userCoinsDecoder = Decode.list userCoinDecoder


-- Add new amount
reqAddCoin : Env.Model -> Keycloak.Struct -> UserCoin -> Request ()
reqAddCoin env kc coin = 
     Http.request
        { method = "POST"
        , headers = [reqAuthHeader kc]
        , url = buildUrlAddCoin env kc
        , body = encodeNewCoinToJson coin
        , expect = expectStringResponse (\_ -> Ok ())
        , timeout = Nothing
        , withCredentials = True
        }

buildUrlAddCoin : Env.Model -> Keycloak.Struct -> String
buildUrlAddCoin env kc = 
    env ++ "/sink/resources/orders"

encodeNewCoinToJson : UserCoin -> Body
encodeNewCoinToJson coin =
    let encode = 
            Encode.object
                [ ( "amount", Encode.float coin.amount )
                , ( "coinSymbol", Encode.string coin.curr )
            ]
    in jsonBody encode
