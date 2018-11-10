import "./main.css";
import { Elm } from "./Main.elm";
import registerServiceWorker from "./registerServiceWorker";

const createKcRealm = oKc => {
  return {
    subject: oKc.subject,
    token: oKc.token
  };
}; 

oKeycloak.onAuthSuccess = () => {
  Elm.Main.init({
    node: document.getElementById("root"),
    flags: createKcRealm(oKeycloak)
  });
}

oKeycloak.onAuthError = () => {
  console.log("Can not be authenticated.");
}

registerServiceWorker();
