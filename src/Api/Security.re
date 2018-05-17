[%%raw "import Keycloak from 'keycloak-js'"];
[%%raw "const keycloak = Keycloak()"];

let query: Js.Promise.t(string) = [%raw "new Promise((resolve, reject) => {keycloak.init({onLoad: 'login-required'}).success(() => resolve(keycloak.subject)).error(error => reject(error))})"];
