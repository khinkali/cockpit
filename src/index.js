import React from "react";
import ReactDOM from "react-dom";

// styles
import "./index.scss";

// js
import { signin } from "./Api/Security.bs";
import App from "./App/AppContainer.bs";

signin()
  .then(text => {
    ReactDOM.render(<App />, document.getElementById("root"));
  })
  .catch(error => {
    console.log("Error occurred!", error);
  });

module.hot.accept();