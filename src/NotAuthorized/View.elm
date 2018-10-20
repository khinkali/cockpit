module NotAuthorized.View exposing (show)

import Html exposing (..)


show : Html a
show =
    p [] [ text "something is wrong with keycloak" ]
