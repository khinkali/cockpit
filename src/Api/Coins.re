[%%raw "import axios from 'axios'"];

type coin = {
  amount: int,
  currency: string,
};

type coins = list(coin);

let transformToCoins = (values: list('a)): coins => {
  List.map(obj => {amount: obj##amount, currency:obj##coinSymbol}, values);
};

let keycloakQuery = (config: Config.env) => 
  Js.Promise.then_(p => {
    let url: string = config.url ++ "/sink/resources/users/" ++ p##subject ++ "/coins";

    let keycloak = Axios.makeConfigWithUrl(~url=url, 
    ~_method="GET", 
    ~headers={"Authorization": "Bearer " ++ p##token},
    ());
  
    Axios.request(keycloak)
    |> Js.Promise.then_(x => Js.Promise.resolve(x));
  }, Security.query);

let request = (c: coins => unit) =>
  Config.read
  |> Js.Promise.then_(x => keycloakQuery(x)) 
  |> Js.Promise.then_(x => Js.Promise.resolve(Array.to_list(x##data)))
  |> Js.Promise.then_(x => Js.Promise.resolve(transformToCoins(x)))
  |> Js.Promise.then_(x => Js.Promise.resolve(c(x)));
