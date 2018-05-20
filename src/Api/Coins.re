type coin = {
  amount: int,
  currency: string,
};

type coins = list(coin);

let transformToCoins = (values: list('a)) : coins =>
  List.map(obj => {amount: obj##amount, currency: obj##coinSymbol}, values);

let reqSecurity = (config: Config.env) =>
  Security.query
  |> Js.Promise.then_((p: Security.pool) => {  
    let url: string = config.url ++ "/sink/resources/users/" ++ p.subject ++ "/coins";
    let httpHeader = Axios.makeConfigWithUrl(~url, ~_method="GET", ~headers={"Authorization": "Bearer " ++ p.token}, ());

    Axios.request(httpHeader);
  });

let request = (c: coins => unit) =>
  Config.read
  |> Js.Promise.then_(x => reqSecurity(x))
  |> Js.Promise.then_(x => Js.Promise.resolve(Array.to_list(x##data)))
  |> Js.Promise.then_(x => Js.Promise.resolve(transformToCoins(x)))
  |> Js.Promise.then_(x => Js.Promise.resolve(c(x)));
