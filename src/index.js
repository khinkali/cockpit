import React from 'react';
import ReactDOM from 'react-dom';

/* Import css */
import 'font-awesome/css/font-awesome.css';
import './index.css'; 

/* Import javascript */
import 'bootstrap';
//import './SbAdmin/js/sb-admin';

import App from './App/AppContainer.bs';
import registerServiceWorker from './registerServiceWorker';

ReactDOM.render(<App />, document.getElementById('root'));
registerServiceWorker();
