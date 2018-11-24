module Account.Page exposing (Msg(..), update, view, Model, init)

import API.Keycloak as Keycloak exposing (..)
import API.Env as Env exposing (..)
import API.Coins as Coins exposing (..)
import Html as Html exposing (..)
import Html.Attributes as Attr exposing (..)
import Http exposing (..)
import Html.Events as Events exposing (..)
import Json.Decode as Decode exposing (..)


---- MODEL ----

type alias NewCoin = { coin: String, currency: String }

type alias Model =
    { 
        env : Env.Model,
        kc : Keycloak.Struct,
        currencies : List String,
        coin : String,
        currency : String,
        disableAdd: Bool,
        userCoins: Coins.UserCoins,
        error : String
    }


init : Env.Model -> Keycloak.Struct -> ( Model, Cmd Msg )
init env kc =
    ( Model env kc [] "" "" True [] "" 
    , Http.send GotCurrencies (Coins.reqCoins env kc)
    )

---- UPDATE ----

type Msg
    = GotCurrencies (Result Http.Error (List String))
    | GotUserCoins (Result Http.Error Coins.UserCoins)
    | GotCoinAdded (Result Http.Error ())
    | OnChangedSelect String
    | OnInputCoin String
    | OnClickAdd
    | ValidNumbers
    | UnvalidNumbers

update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        GotCurrencies resp ->
            case resp of
                Ok value ->
                    ({model | currencies = value}, queryUserCoins model.env model.kc)
                Err _ ->
                    ({model | error = "Can not query coins currency" }, Cmd.none)
        GotUserCoins resp ->
            case resp of
                Ok value ->
                    ({model | userCoins = value}, Cmd.none)
                Err _ ->
                    (model, Cmd.none)
        GotCoinAdded resp ->
            case resp of
                Ok value ->
                    (resetValues model, queryUserCoins model.env model.kc)
                Err _ ->
                    ({model | error = "Error occurs during add new coin." }, Cmd.none)
        OnChangedSelect curr ->
            ({model | currency = curr, disableAdd = (setAddStatus model.coin curr)}, Cmd.none)
        OnInputCoin value ->
            ({model | coin = value, disableAdd = (setAddStatus value model.currency)}, Cmd.none)
        OnClickAdd ->
            case (String.toFloat model.coin) of
                Just value ->
                    (model, sendAddCoin model.env model.kc (Coins.UserCoin value model.currency))
                Nothing ->
                    ({model | error = "Coin amount is not valid."}, Cmd.none)
        ValidNumbers ->
            ({model | error = "" }, Cmd.none)
        UnvalidNumbers ->
            (model, Cmd.none)
            

--- SUBSCRIPTIONS ---

subscriptions : Model -> Sub Msg
subscriptions model =
    Sub.none 


---- VIEW ----


view : Model -> Html Msg
view model =
    div [] [
        input [id "inputAmt", Attr.type_ "number", Attr.min "0", Events.onInput OnInputCoin , preventCharPress, Attr.value model.coin, Attr.step "0.001"] [],
        select [id "selectCurr", Attr.value model.currency, onChangeCurrency]  <| buildCurrencyOption model.currencies,
        button [id "btnAdd", onClick OnClickAdd, disabled model.disableAdd ] [ text "Add" ],
        p [] [text model.error],
        userCoinsView model.userCoins
    ]

userCoinsView : Coins.UserCoins -> Html Msg
userCoinsView userCoins = 
    let header = tr [] [th [] [text "Amount"],th [] [text "Currency"]]
        data = List.map (\x -> tr [] [td [] [text (String.fromFloat x.amount)], td [] [text x.curr]]) userCoins
    in table [ id "tableCoins" ] (header :: data)


---- FUNCTIONS ----

-- Prevent the letter e press
preventCharPress : Attribute Msg
preventCharPress =
    preventDefaultOn "keydown"
    (Decode.field "keyCode" Decode.int
        |> Decode.andThen
        (\key ->
            if key == 69 || key == 189 || key == 109 then
                Decode.succeed (UnvalidNumbers, True)
            else
                Decode.succeed (ValidNumbers, False)
        )
    )

setAddStatus : String -> String -> Bool
setAddStatus amt curr = 
    if (String.length amt > 0) && (String.length curr > 0) then
      False
    else 
      True

sendAddCoin : Env.Model -> Keycloak.Struct -> Coins.UserCoin -> Cmd Msg
sendAddCoin env kc coin = 
    Http.send GotCoinAdded (Coins.reqAddCoin env kc coin)

queryUserCoins :  Env.Model -> Keycloak.Struct -> Cmd Msg
queryUserCoins env kc =
    Http.send GotUserCoins (Coins.reqUserCoins env kc)


resetValues : Model -> Model
resetValues model = 
    {model| coin = "", currency = "", disableAdd = True}

buildCurrencyOption : List String -> List (Html Msg)
buildCurrencyOption list = 
    let tail =
            List.map (\x -> option [Attr.value x] [text x]) list
        head = 
            option [Attr.value "", Attr.selected True, Attr.disabled True] [text ""]
    in head :: tail 

onChangeCurrency : Attribute Msg
onChangeCurrency = Events.on "change" (Decode.map (\value -> OnChangedSelect value) Events.targetValue)
