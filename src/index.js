import "./main.css";
import { Elm } from "./Main.elm";
import registerServiceWorker from "./registerServiceWorker";
import Keycloak from "keycloak-js";

const oKeycloak = Keycloak("config/keycloak.json");

oKeycloak
  .init({ onLoad: "login-required" })
  .success(oAuth => console.log(oAuth))
  .error(console.log);

/* Elm.Main.init({
  node: document.getElementById("root")
}); */

registerServiceWorker();
