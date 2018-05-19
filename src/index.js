import React from 'react';
import ReactDOM from 'react-dom';

// js
import {authorize} from './Api/Security';
import 'bootstrap';

// styles
import './index.scss';
import App from './App/AppContainer.bs';

authorize
.then((text) => {
  ReactDOM.render(<App/>, document.getElementById('root'));
}).catch((error) => {
  console.log('Error occurred!', error);
});



