%raw
"import Keycloak from 'keycloak-js'";

%raw
"const keycloak = Keycloak()";

type pool = {
  .
  "subject": string,
  "token": string,
};

let query: Js.Promise.t(pool) = [%raw
  {|
  new Promise((resolve, reject) => {
    keycloak.init({
        onLoad: 'login-required'
      }).success(() => resolve({subject: keycloak.subject, token: keycloak.token})).error(error => reject(error))
    })
  |}
];
