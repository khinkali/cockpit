type url = string;

type data = Js.Dict.t(string);

[@bs.deriving abstract]
type config = {
  [@bs.optional]
  headers: Js.Dict.t(string),
};

[@bs.module "axios"]
external axget : (~url: url, ~config: config=?, unit) => Js.Promise.t('a) =
  "get";

[@bs.module "axios"]
external axpost :
  (~url: url, ~data: data, ~config: config) => Js.Promise.t('a) =
  "post";

let get = (url: url) => axget(~url, ());
let getWithConfig = (url: url, config: config) => axget(~url, ~config, ());

let postWithConfig = (url: url, data: data, config: config) =>
  axpost(~url, ~data, ~config);