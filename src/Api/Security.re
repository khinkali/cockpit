[%%raw "import Keycloak from 'keycloak-js'"];
[%%raw "const keycloak = Keycloak()"];

let init : Js.Promise.t(unit) = [%raw "keycloak.init({onLoad: 'login-required'})"];

let query = init
            |> Js.Promise.then_(_ => Js.Promise.resolve([%raw "keycloak.subject"]));
