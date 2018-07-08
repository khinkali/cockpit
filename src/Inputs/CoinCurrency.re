type state = {currs: Coins.currencies};

type action =
  | SelectedCurr(string)
  | FetchCurr(Coins.currencies);

let component = ReasonReact.reducerComponent("CoinCurrecy");

let make = _children => {
  ...component,
  initialState: () => {currs: []},
  didMount: self =>
    Coins.getCurrencies(currs => self.send(FetchCurr(currs))) |> ignore,
  reducer: (action, _state) =>
    switch (action) {
    | SelectedCurr(_curr) => ReasonReact.NoUpdate
    | FetchCurr(currs) => ReasonReact.Update({currs: currs})
    },
  render: _self => 
    <div />
};