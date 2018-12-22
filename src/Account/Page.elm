module Account.Page exposing (Model, Msg(..), init, update, view)

import Account.Coins as Coins
import Error.Page as Error
import Html as Html exposing (..)
import Html.Attributes as Attr exposing (..)
import Html.Events as Events exposing (..)
import Http exposing (..)
import Json.Decode as Decode exposing (..)
import Security.Data as Security



---- MODEL ----


type alias NewCoin =
    { amount : String, currency : String }


type alias Model =
    { sec : Security.Model
    , newCoin : NewCoin
    , coins : Coins.Model
    , disableAdd : Bool
    , error : Error.Status
    }


initNewCoin : NewCoin
initNewCoin =
    NewCoin "" ""


init : Security.Model -> ( Model, Cmd Msg )
init sec =
    ( Model Security.init initNewCoin Coins.init True Error.Success
    , Cmd.map OnCoins (Coins.reqCoinCurrencies sec)
    )



---- UPDATE ----


type Msg
    = OnCoins Coins.Msg
    | OnCurrenySelect String
    | OnCoinAmt String
    | OnClickAdd
    | OnNotNumber


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        OnCoins coinsMsg ->
            handleUpdateCoins model (Coins.update coinsMsg model.coins)

        OnCurrenySelect selectedCurrency ->
            ( setAddStatus (setNewCoinCurrency (NewCoin "" selectedCurrency) model), Cmd.none )

        OnCoinAmt value ->
            ( setAddStatus (setNewCoinCurrency (NewCoin value "") model), Cmd.none )

        OnClickAdd ->
            addNewCoin model.newCoin model

        OnNotNumber ->
            ( model, Cmd.none )



--- SUBSCRIPTIONS ---


subscriptions : Model -> Sub Msg
subscriptions model =
    Sub.none



---- VIEW ----


view : Model -> Html Msg
view model =
    div []
        [ addCoinSection model
        , coinsView model.coins.account
        ]


addCoinSection : Model -> Html Msg
addCoinSection model =
    section [ id "add-new-coin" ]
        [ input [ name "newamount", Attr.type_ "number", Attr.min "0", Events.onInput OnCoinAmt, preventCharPress, Attr.value model.newCoin.amount, Attr.step "0.001" ] []
        , select [ name "newcurrency", Attr.value model.newCoin.currency, onCurrencyChange ] <| buildCurrencyOption model.coins.currencies
        , button [ name "addnewcoin", onClick OnClickAdd, disabled model.disableAdd ] [ text "Add" ]
        ]


coinsView : Coins.Account -> Html Msg
coinsView account =
    let
        header =
            thead [] [ tr [] [ th [] [ text "Amount" ], th [] [ text "Currency" ] ] ]

        row =
            List.map coinsRow

        data =
            tbody [] (row account)
    in
    section [ id "coin-overview" ] [ table [ id "coins-table" ] [ header, data ] ]


coinsRow : Coins.Coin -> Html Msg
coinsRow coin =
    tr [] [ td [] [ text (String.fromFloat coin.amount) ], td [] [ text coin.currency ] ]



---- FUNCTIONS ----
-- Prevent the letter e press


preventCharPress : Attribute Msg
preventCharPress =
    preventDefaultOn "keydown"
        (Decode.field "keyCode" Decode.int
            |> Decode.andThen
                (\key ->
                    if key == 69 || key == 189 || key == 109 then
                        Decode.succeed ( OnNotNumber, True )

                    else
                        Decode.succeed ( OnNotNumber, False )
                )
        )


setNewCoinCurrency : NewCoin -> Model -> Model
setNewCoinCurrency newCoin model =
    if String.length newCoin.amount > 0 then
        { model | newCoin = NewCoin newCoin.amount "" }

    else if String.length newCoin.currency > 0 then
        { model | newCoin = NewCoin "" newCoin.currency }

    else
        model


setAddStatus : Model -> Model
setAddStatus model =
    if (String.length model.newCoin.amount > 0) && (String.length model.newCoin.currency > 0) then
        { model | disableAdd = False }

    else
        { model | disableAdd = True }


resetValues : Model -> Model
resetValues model =
    { model | newCoin = initNewCoin, disableAdd = True }


buildCurrencyOption : List String -> List (Html Msg)
buildCurrencyOption list =
    let
        tail =
            List.map (\x -> option [ Attr.value x ] [ text x ]) list

        head =
            option [ Attr.value "", Attr.selected True, Attr.disabled True ] [ text "" ]
    in
    head :: tail


onCurrencyChange : Attribute Msg
onCurrencyChange =
    Events.on "change" (Decode.map (\value -> OnCurrenySelect value) Events.targetValue)


handleUpdateCoins : Model -> ( Coins.Model, Cmd Coins.Msg ) -> ( Model, Cmd Msg )
handleUpdateCoins model ( cModel, cMsg ) =
    ( { model | coins = cModel }, Cmd.map OnCoins cMsg )


addNewCoin : NewCoin -> Model -> ( Model, Cmd Msg )
addNewCoin newCoin model =
    case String.toFloat newCoin.amount of
        Just value ->
            ( model, Cmd.map OnCoins <| Coins.reqAddCoin model.sec <| Coins.Coin value newCoin.currency )

        Nothing ->
            ( { model | error = Error.Failed "Add not new coin." }, Cmd.none )
