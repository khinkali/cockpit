import Keycloak from 'keycloak-js';

const keycloak = Keycloak();

const authorize = new Promise((resolve, reject) => {
  keycloak
    .init({
      onLoad: 'login-required'
    })
    .success((authenticated) => {
      if (authenticated) {
        resolve('You are authenticated.');
      } else {
        reject('You are not authenticated');
      }
    })
    .error(function() {
      reject('Failed to initialize');
    });;
});

export { authorize };
