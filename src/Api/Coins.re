[@bs.deriving abstract]
type rawCoin = {
  amount: float,
  coinSymbol: string,
};

type rawCoins = array(rawCoin);

type coin = {
  amount: float,
  currency: string,
};

type currencies = array(string);

type coins = array(coin);

/* let transform = (values: list('a)) : coins =>
  List.map(obj => {amount: obj##amount, currency: obj##coinSymbol}, values); */

let authorize = () =>
  Config.read
  |> Js.Promise.then_((e: Config.env) =>
       Security.authorize()
       |> Js.Promise.then_((keys: Security.kcKeys) =>
            Js.Promise.resolve((e, keys))
          )
     );

/* Query all crypto currencies from server. */
let fetchCurrs = (currs: currencies => unit) =>
  authorize()
  |> Js.Promise.then_(data => {
       let (config: Config.env, keys: Security.kcKeys) = data;
       let url = config.url ++ "/sink/resources/coins";
       let headers =
         Js.Dict.fromArray([|("Authorization", "Bearer " ++ keys.token)|]);

       Axios.getWithConfig(url, Axios.config(~headers, ()));
     })
  |> Js.Promise.then_((resp: Axios.response(currencies, 'b)) =>
       Js.Promise.make((~resolve, ~reject) =>
         if (Axios.statusGet(resp) != 200) {
           reject(.
             Js.Exn.raiseError("Could not find the coins currencies."),
           );
         } else {
           resolve(. Axios.dataGet(resp));
         }
       )
     )
  |> Js.Promise.then_(c => Js.Promise.resolve(currs(c)));

let get = (c: coins => unit) =>
  authorize()
  |> Js.Promise.then_(data => {
       let (config: Config.env, keys: Security.kcKeys) = data;
       let url =
         config.url ++ "/sink/resources/users/" ++ keys.subject ++ "/coins";
       let headers =
         Js.Dict.fromArray([|("Authorization", "Bearer " ++ keys.token)|]);
       Axios.getWithConfig(url, Axios.config(~headers, ()));
     })
  |> Js.Promise.then_((resp: Axios.response(rawCoins, 'b)) => {

     let data = Axios.dataGet(resp)
     |. Belt.Array.map(x => {amount: amountGet(x), currency: coinSymbolGet(x)});

     Js.Promise.resolve(c(data));
  });

let post = (newCoin: coin) =>
  Config.read
  |> Js.Promise.then_((x: Config.env) => {
      
      let url = x.url ++ "/sink/resources/orders";
      let data = rawCoin(~amount=newCoin.amount, ~coinSymbol=newCoin.currency);

       Security.authorize()
       |> Js.Promise.then_((keys: Security.kcKeys) => {
            let headers =
              Js.Dict.fromArray([|
                ("Authorization", "Bearer " ++ keys.token),
              |]);

            Axios.postWithConfig(url, data, Axios.config(~headers, ()));
          });
     })
  |> Js.Promise.then_((resp: Axios.response('a, 'b)) => {
    let a = Axios.statusGet(resp);

    Js.Promise.make((~resolve, ~reject) =>
         if (a != 202) {
           reject(.
             Js.Exn.raiseError("Could not add coin successfully."),
           );
         } else {
           resolve(. "Successfull added.");
         }
       )

  });