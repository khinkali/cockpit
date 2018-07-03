type coin = {
  amount: int,
  currency: string,
};

type coins = list(coin);

let transform = (values: list('a)) : coins =>
  List.map(obj => {amount: obj##amount, currency: obj##coinSymbol}, values);

let authorize = () =>
  Config.read
  |> Js.Promise.then_((e: Config.env) =>
       Security.authorize()
       |> Js.Promise.then_((keys: Security.kcKeys) =>
            Js.Promise.resolve((e, keys))
          )
     );

let get = (c: coins => unit) =>
  authorize()
  |> Js.Promise.then_((data) => {
       let (config: Config.env, keys: Security.kcKeys) = data;
       let url =
         config.url ++ "/sink/resources/users/" ++ keys.subject ++ "/coins";
       let headers =
         Js.Dict.fromArray([|("Authorization", "Bearer " ++ keys.token)|]);
       Axios.getWithConfig(url, Axios.config(~headers, ()));
     })
  |> Js.Promise.then_(x => Js.Promise.resolve(Array.to_list(x##data)))
  |> Js.Promise.then_(x => Js.Promise.resolve(transform(x)))
  |> Js.Promise.then_(x => Js.Promise.resolve(c(x)))
  |> Js.Promise.catch(err => Js.Promise.resolve(Js.log(err)));

let post = (addCoin: coin, handler: Axios.status => unit) =>
  Config.read
  |> Js.Promise.then_((x: Config.env) => {
       let url = x.url ++ "/sink/resources/orders";

       let data =
         Js.Dict.fromArray([|
           ("coinSymbol", addCoin.currency),
           ("amount", string_of_int(addCoin.amount)),
         |]);

       Security.authorize()
       |> Js.Promise.then_((keys: Security.kcKeys) => {
            let headers =
              Js.Dict.fromArray([|
                ("Authorization", "Bearer " ++ keys.token),
              |]);
            Axios.postWithConfig(url, data, Axios.config(~headers, ()));
          });
     })
  |> Js.Promise.then_(x => Js.Promise.resolve(Js.log(x)));