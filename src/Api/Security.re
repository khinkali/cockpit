module Keycloak = {
  [@bs.deriving abstract]
  type t = {
    authenticated: bool,
    token: string,
    subject: string,
    idToken: string,
  };
};

type kcInit;
type kcKeys = {
  token: string,
  subject: string,
  idToken: string,
};

[@bs.deriving abstract]
type initConfig = {onLoad: string}; 

[@bs.module "keycloak-js"] external keycloak : string => Keycloak.t = "default";
[@bs.send] external init : (Keycloak.t, initConfig) => kcInit = "";
[@bs.send] external success : (kcInit, bool => unit) => kcInit = "";
[@bs.send] external error : (kcInit, unit => unit) => unit = "";

let kc = keycloak("config/keycloak.json");

let signin = () =>
  Js.Promise.make((~resolve, ~reject) =>
    kc
    |. init(initConfig(~onLoad="login-required"))
    |. success(autheticated =>
         autheticated ?
           resolve(. "authenticated") :
           reject(. Js.Exn.raiseError("Your are not authenticated!"))
       )
    |. error(() =>
         reject(.
           Js.Exn.raiseError("There is something wrong with keycloak"),
         )
       )
  );


let authorize = () =>
  Js.Promise.make((~resolve, ~reject) =>
    if(!Keycloak.authenticated(kc)) {
      reject(. Js.Exn.raiseError("Your are not authroized."))
    } else {
      let keys: kcKeys = {
        token: Keycloak.token(kc),
        subject: Keycloak.subject(kc),
        idToken: Keycloak.idToken(kc),
      };
      resolve(. keys);
    }
  );