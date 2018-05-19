import Keycloak from 'keycloak-js';

const keycloak = Keycloak();

keycloak
.init({onLoad: 'login-required'});
.success((authenticated) => {
  if(authenticated){
    console.log('authenticated');
  } else {
    console.log('not authenticated');
  }
})