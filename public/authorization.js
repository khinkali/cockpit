var keycloak = Keycloak();
keycloak.init({
  onLoad: 'login-required'
}).success(function (authenticated) {
  console.log(authenticated ? 'authenticated' : 'not authenticated');
}).error(function () {
  console.log('failed to initialize');
});

var loadData = function () {

  var url = 'http://5.189.154.24:31081/sink/resources/users/'  + keycloak.subject + '/coins';

  var req = new XMLHttpRequest();
  req.open('GET', url, true);
  req.setRequestHeader('Accept', 'application/json');
  req.setRequestHeader('Authorization', 'Bearer ' + keycloak.token);

  req.onreadystatechange = function () {
    if (req.readyState == 4) {
      if (req.status == 200) {
        console.log('Success');
      } else if (req.status == 403) {
        console.log('Forbidden');
      }
    }
  }

  req.send();
};