
let read =
  Axios.get("config.json")
  |> Js.Promise.then_(x => Js.Promise.resolve(x##data##env##url))
  |> Js.Promise.then_(x => Js.Promise.resolve(x));

