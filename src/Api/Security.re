[%%raw "import Keycloak from 'keycloak-js'"];
[%%raw "const keycloak = Keycloak()"];

let query: Js.Promise.t(string) = [%raw "keycloak.init({onLoad: 'login-required'}).success(function (authenticated) {return new Promise.resolve('authenticated');})"];
