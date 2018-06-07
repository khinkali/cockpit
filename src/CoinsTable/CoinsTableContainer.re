type state = {coins: Coins.coins};

type action =
  | Query(Coins.coins);

let component = ReasonReact.reducerComponent("CoinsTableContainer");

let make = _children => {
  ...component,
  initialState: () => {coins: []},
  didMount: self => {
    Coins.request((c) => self.send(Query(c)))
    |> ignore;
  },
  reducer: (action, _state) =>
    switch (action) {
    | Query(cs) => ReasonReact.Update({coins: cs})
    },
  render: self => <CoinsTableView coins=self.state.coins />,
};