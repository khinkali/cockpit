module Menu.Page exposing (..)

import Html exposing (..)
import Html.Attributes exposing (..)



type Msg =
    CallMenu

content : Html Msg
content = header [id "menu-navi"] []



