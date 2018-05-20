import React from "react";
import ReactDOM from "react-dom";

// styles
import "./index.scss";

// js
import "bootstrap";
import { authorize } from "./Api/Security.bs";
import App from "./App/AppContainer.bs"; 

//ReactDOM.render(<App />, document.getElementById("root"));

authorize()
.then((text) => {
  ReactDOM.render(<App/>, document.getElementById('root'));
}).catch((error) => {
  console.log('Error occurred!', error);
});
