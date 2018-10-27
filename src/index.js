import "./main.css";
import { Elm } from "./Main.elm";
import registerServiceWorker from "./registerServiceWorker";
import Keycloak from "keycloak-js";

const oKeycloak = Keycloak("config/keycloak.json");

const entryElm = bAuth => {
  
  if (bAuth) {
    Elm.Main.init({
      node: document.getElementById("root"),
      flags: createKcRealm(oKeycloak)
    });
  } else {
    console.log("Sorry, you are not authenticated.");
  }
};

const createKcRealm = oKc => {
  return {
    subject: oKc.subject,
    token: oKc.token
  };
}; 

oKeycloak
  .init({ onLoad: "login-required" })
  .success(entryElm)
  .error(console.log);

registerServiceWorker();
