module KeycloakTest exposing (all)

import API.Keycloak exposing (..)
import Expect
import Json.Encode as Encode
import Test exposing (..)


valid : Encode.Value
valid =
    Encode.object
        [ ( "subject", Encode.string "4PXoA03hDV" )
        , ( "token", Encode.string "GEPnrLuM2E" )
        ]


invalid : Encode.Value
invalid =
    Encode.object
        [ ( "subj", Encode.string "4PXoA03hDV" )
        , ( "tok", Encode.string "GEPnrLuM2E" )
        ]


emptyValue : Encode.Value
emptyValue =
    Encode.object
        [ ( "subject", Encode.string "" )
        , ( "token", Encode.string "" )
        ]


all : Test
all =
    describe "Keycloak test data"
        [ test "Valid authentication" <|
            \_ ->
                Expect.ok (validate valid)
        , test "Invalid authentication" <|
            \_ ->
                Expect.err <| validate invalid
        , test "Invalid empty values" <|
            \_ ->
                Expect.err <| validate emptyValue
        ]
