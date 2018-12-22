port module Security.Data exposing (Model, Msg(..), doPubKc, envFailed, init, kcFailed, onSubKc, update)

import Browser.Navigation as Nav
import Error.Page exposing (..)
import Http
import Json.Decode exposing (..)
import Security.Env as Env
import Security.Keycloak as Keycloak
import Url


port doPubKc : () -> Cmd msg


port onSubKc : (Value -> msg) -> Sub msg


type alias Model =
    { env : Env.Model
    , kc : Keycloak.Model
    , status : Status
    }


init : Model
init =
    Model Env.init Keycloak.init Success


type Msg
    = OnEnv (Result Http.Error String)
    | OnSubKc Keycloak.Token


update : Msg -> Model -> ( Model, Cmd Msg )
update msg model =
    case msg of
        OnEnv res ->
            case res of
                Ok succ ->
                    ( { model | env = succ }, Cmd.none )

                Err _ ->
                    ( { model | status = envFailed }, Cmd.none )

        OnSubKc value ->
            case value of
                Ok succ ->
                    ( { model | kc = succ }, Env.reqEnv OnEnv )

                Err _ ->
                    ( { model | status = kcFailed }, Cmd.none )


envFailed : Status
envFailed =
    Failed "Can not query enviroment variable"


kcFailed : Status
kcFailed =
    Failed "Can not get authorization from keycloak"
