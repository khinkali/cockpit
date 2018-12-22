module Account.Coins exposing (Account, Coin, Model, Msg, init, reqAccount, reqAddCoin, reqCoinCurrencies, update)

import Error.Page as Error
import Http exposing (..)
import Json.Decode as Decode
import Json.Encode as Encode
import Security.Data as Security


type alias Coin =
    { amount : Float
    , currency : String
    }


type alias Account =
    List Coin


type Msg
    = OnCoinsCurrenry (Result Error (List String))
    | OnAccount (Result Error Account)
    | OnAddCoin (Result Error ())


type alias Model =
    { currencies : List String
    , account : Account
    , sec : Security.Model
    , error : Error.Status
    }


init : Model
init =
    Model [] [] Security.init Error.Success


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        OnCoinsCurrenry resp ->
            case resp of
                Ok value ->
                    ( { model | currencies = value }, Cmd.none )

                Err err ->
                    ( { model | error = Error.Failed "Can not read currencies." }, Cmd.none )

        OnAccount resp ->
            case resp of
                Ok value ->
                    ( { model | account = value }, Cmd.none )

                Err err ->
                    ( { model | error = Error.Failed "Can not read stored user coins." }, Cmd.none )

        OnAddCoin resp ->
            case resp of
                Ok value ->
                    ( model, reqAccount model.sec )

                Err err ->
                    ( { model | error = Error.Failed "Can not read stored user coins." }, Cmd.none )


reqCoinCurrencies : Security.Model -> Cmd Msg
reqCoinCurrencies sec =
    Http.request
        { method = "GET"
        , headers = [ reqAuthHeader sec ]
        , url = buildUrlCurrs sec
        , body = emptyBody
        , expect = Http.expectJson OnCoinsCurrenry (Decode.list Decode.string)
        , timeout = Nothing
        , tracker = Nothing
        }


reqAuthHeader : Security.Model -> Http.Header
reqAuthHeader sec =
    Http.header "Authorization" ("Bearer " ++ sec.kc.token)



-- Url for query coin currencies


buildUrlCurrs : Security.Model -> String
buildUrlCurrs sec =
    sec.env ++ "/sink/resources/coins"



-- Get all user coins


reqAccount : Security.Model -> Cmd Msg
reqAccount sec =
    Http.request
        { method = "GET"
        , headers = [ reqAuthHeader sec ]
        , url = buildUrlAccountCoins sec
        , body = emptyBody
        , expect = Http.expectJson OnAccount accountDecoder
        , timeout = Nothing
        , tracker = Nothing
        }


buildUrlAccountCoins : Security.Model -> String
buildUrlAccountCoins sec =
    sec.env ++ "/sink/resources/users/" ++ sec.kc.subject ++ "/coins"


amountDecoder : Decode.Decoder Float
amountDecoder =
    Decode.field "amount" Decode.float


currencyDecoder : Decode.Decoder String
currencyDecoder =
    Decode.field "coinSymbol" Decode.string


coinDecoder : Decode.Decoder Coin
coinDecoder =
    Decode.map2 Coin amountDecoder currencyDecoder


accountDecoder : Decode.Decoder Account
accountDecoder =
    Decode.list coinDecoder



-- Add new amount


reqAddCoin : Security.Model -> Coin -> Cmd Msg
reqAddCoin sec coin =
    Http.request
        { method = "POST"
        , headers = [ reqAuthHeader sec ]
        , url = buildUrlAddCoin sec
        , body = encodeNewCoinToJson coin
        , expect = expectWhatever OnAddCoin
        , timeout = Nothing
        , tracker = Nothing
        }


buildUrlAddCoin : Security.Model -> String
buildUrlAddCoin sec =
    sec.env ++ "/sink/resources/orders"


encodeNewCoinToJson : Coin -> Body
encodeNewCoinToJson coin =
    let
        encode =
            Encode.object
                [ ( "amount", Encode.float coin.amount )
                , ( "coinSymbol", Encode.string coin.currency )
                ]
    in
    jsonBody encode
