module Menu.Page exposing (..)

import Html exposing (..)
import Html.Attributes exposing (..)



type Msg =
    CallMenu

content : Html Msg
content = header [id "menu-navi", class "container"] [
        div [class "columns"] [
            section [class "column col-md-12 col-xl-8 col-5 col-mx-auto"] [
                navbar
            ]
        ]
    ]

navbar : Html Msg
navbar = section [class "navbar"] [
            section [class "navbar-section"] [
                img [id "logo", src "./images/expensive.svg"] []
            ],
            section [class "navbar-section"] [
                button [class "btn btn-lg"] [
                    i [class "fas fa-bars", style "padding-right" "10px"] [], text "Menu"
                ]
            ]
        ] 



