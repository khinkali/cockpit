import "./main.css";
import { Elm } from "./Main.elm";
import registerServiceWorker from "./registerServiceWorker";
import Keycloak from "keycloak-js";

const oKeycloak = Keycloak("config/keycloak.json");

const entryElm = bAuth => {
  if (bAuth) {

    Elm.Main.init({
      node: document.getElementById("root")
    });
  } else {
    console.log("Sorry, you are not authenticated.");
  }
};

const createKcRealm = oKc => {

  const oKcProps = {
    "subject": oKc.subject,
    "token": oKc.token,
  };

  return JSON.stringify(oKcProps);
};

oKeycloak
  .init({ onLoad: "login-required" })
  .success(entryElm)
  .error(console.log);

registerServiceWorker();
