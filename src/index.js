import React from "react";
import ReactDOM from "react-dom";

// styles
import "./index.scss";

// js
import { signin } from "./Api/Security.bs";
import App from "./App/App.bs";

signin()
	.then((text) => {
		ReactDOM.render(<App />, document.getElementById('root'));
	})
	.catch((error) => {
		console.log('Error occurred!', error);
	});
	
ReactDOM.render(<App />, document.getElementById("root"));

// Only for development server
if (module.hot) {
  module.hot.accept();
}
