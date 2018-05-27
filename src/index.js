import React from "react";
import ReactDOM from "react-dom";

// styles
import "./index.scss";

// js
import { authorize } from "./Api/Security.bs";
import App from "./App/AppContainer.bs"; 

authorize()
.then((text) => {
  ReactDOM.render(<App/>, document.getElementById('root'));
}).catch((error) => {
  console.log('Error occurred!', error);
});
