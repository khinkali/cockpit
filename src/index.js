import React from 'react';
import ReactDOM from 'react-dom';
import 'font-awesome/css/font-awesome.css';
import './index.css';
import 'bootstrap';
//import Keycloak from 'keycloak-js';
//import axios from "axios";

import App from './App/AppContainer.bs';
import registerServiceWorker from './registerServiceWorker';

ReactDOM.render(<App/>, document.getElementById('root'));
registerServiceWorker();

/*const kc = Keycloak();
kc.init({onLoad: 'login-required'}).success(authenticated => {
    if (authenticated) {
        ReactDOM.render(<App/>, document.getElementById('root'));
        registerServiceWorker();
    }
});

axios.interceptors.request.use(config => {
    return refreshToken().then(() => {
        config.headers.Authorization = 'Bearer ' + kc.token;
        return Promise.resolve(config)
    }).catch(() => {
        kc.login();
    })
});

// need to wrap the KC "promise object" into a real Promise object
const refreshToken = (minValidity = 5) => {
    return new Promise((resolve, reject) => {
        kc.updateToken(minValidity)
            .success(() => resolve())
            .error(error => reject(error))
    });
};*/
