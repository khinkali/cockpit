[%%raw "import Keycloak from 'keycloak-js'"];
[%%raw "const keycloak = Keycloak()"];

let query = init
            |> Js.Promise.then_(_ => Js.Promise.resolve([%raw "keycloak.init({onLoad: 'login-required'}).success(function (authenticated) {return new Promise.resolve('authenticated');})"]));
