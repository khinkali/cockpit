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

[@bs.deriving abstract]
type initConfig = {onLoad: string}; 


[@bs.module "keycloak-js"] external keycloak : string => Keycloak.t = "default";
[@bs.send] external init : (Keycloak.t, initConfig) => kcInit = "";
[@bs.send] external success : (kcInit, bool => unit) => kcInit = "";
[@bs.send] external error : (kcInit, unit => unit) => unit = "";

let kc = keycloak("config/keycloak.json");

let authorize = () =>
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

let kcAuth = Keycloak.authenticated(kc);
let kcToken = Keycloak.token(kc); 
let kcSubject = Keycloak.subject(kc);
let kcIdToken = Keycloak.idToken(kc);