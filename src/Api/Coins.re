type coin = {
  amount: int,
  currency: string,
};

type coins = list(coin);

let transform = (values: list('a)) : coins =>
  List.map(obj => {amount: obj##amount, currency: obj##coinSymbol}, values);

let get = (c: coins => unit) =>
  Config.read
  |> Js.Promise.then_((x: Config.env) => {
       let url =
         x.url ++ "/sink/resources/users/" ++ Security.kcSubject ++ "/coins";
       let headers = Js.Dict.empty();

       Js.Dict.set(headers, "Authorization", "Bearer " ++ Security.kcToken);

       Axios.getWithConfig(url, Axios.config(~headers, ()));
     })
  |> Js.Promise.then_(x => Js.Promise.resolve(Array.to_list(x##data)))
  |> Js.Promise.then_(x => Js.Promise.resolve(transform(x)))
  |> Js.Promise.then_(x => Js.Promise.resolve(c(x)));