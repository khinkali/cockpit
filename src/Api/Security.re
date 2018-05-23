%raw
"import Keycloak from 'keycloak-js'";

%raw
"const keycloak = Keycloak('config/keycloak.json')";

type pool = {
  token: string,
  subject: string,
  idToken: string,
};

/* Promise is wrapped into a function, because it raises controllable initialization */
let authorize: unit => Js.Promise.t(string) =
  () => [%raw
    {|
  new Promise((resolve, reject) => {
    keycloak
      .init({
        onLoad: 'login-required'
      })
      .success(authenticated => {
        if (authenticated) {
          resolve('You are authenticated.');
        } else {
          reject('You are not authenticated');
        }
      })
      .error(function() {
        reject('Failed to initialize');
      });
  })
  |}
  ];

let query = () =>
  Js.Promise.make((~resolve, ~reject) => {
    let authenticated: bool = [%raw "keycloak.authenticated"];
    if (! authenticated) {
      reject(. Js.Exn.raiseError("Your are not authorized!"));
    } else {
      let token: string = [%raw "keycloak.token"];
      let subject: string = [%raw "keycloak.subject"];
      let idToken: string = [%raw "keycloak.idToken"];
      resolve(. {token, subject, idToken});
    };
  });
