var keycloak = Keycloak();
keycloak.init({
  onLoad: 'login-required'
}).success(function (authenticated) {
  alert(authenticated ? 'authenticated' : 'not authenticated');
}).error(function () {
  alert('failed to initialize');
});

var loadData = function () {
  document.getElementById('username').innerText = keycloak.username;

  var url = 'http://5.189.154.24:31081/sink/resources/users/'  + keycloak.subject + '/coins';

  var req = new XMLHttpRequest();
  req.open('GET', url, true);
  req.setRequestHeader('Accept', 'application/json');
  req.setRequestHeader('Authorization', 'Bearer ' + keycloak.token);

  req.onreadystatechange = function () {
    if (req.readyState == 4) {
      if (req.status == 200) {
        alert('Success');
      } else if (req.status == 403) {
        alert('Forbidden');
      }
    }
  }

  req.send();
};


keycloak.updateToken(30).success(function () {
    loadData();
  }).error(function () {
      alert('Failed to refresh token');
  });