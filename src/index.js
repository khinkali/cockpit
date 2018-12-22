import "./main.css";
import { Elm } from "./Main.elm";
import registerServiceWorker from "./registerServiceWorker";


 const createKcRealm = oKc => {
  return {
    subject: oKc.subject,
    token: oKc.token
  };
}; 


oKeycloak.onAuthError = () => {
  console.log("Can not be authenticated.");
}

oKeycloak.onReady = (authenticated) => {
  if (authenticated) {
    const app =  Elm.Main.init({node: document.getElementById("root")});
    app.ports.onSubKc.send(createKcRealm(oKeycloak));
  }
}

registerServiceWorker();
