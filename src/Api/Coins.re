type coin = {
  amount: int,
  currency: string,
};

type coins = list(coin);

let transformToCoins = (values: list('a)): coins => {
  List.map(obj => {amount: obj##amount, currency:obj##coinSymbol}, values);
};

let request = (c: coins => unit) =>
  Config.read
  |> Js.Promise.then_((x: Config.env)  => Axios.get(x.url ++ ""/sink/resources/users/"  + keycloak.subject + "/coins"))
  |> Js.Promise.then_(x => Js.Promise.resolve(Array.to_list(x##data)))
  |> Js.Promise.then_(x => Js.Promise.resolve(transformToCoins(x)))
  |> Js.Promise.then_(x => Js.Promise.resolve(c(x)));
