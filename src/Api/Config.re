[@bs.deriving abstract]
type urlRaw = {
  url: string
};

[@bs.deriving abstract]
type envRaw = {
  [@bs.as "env"] urlRaw_: urlRaw
};

type env = {
  url: string
};

let read =
  Axios.get("config/config.json")
  |> Js.Promise.then_((x: Axios.response(envRaw, 'b)) => {
      let a = Axios.data(x)
              |. urlRaw_
              |. url;
      let b: env = {url: a};
      Js.Promise.resolve(b);
    });

 