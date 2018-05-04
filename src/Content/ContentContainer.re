type state = {
  coins: Coins.coins
};

type action =
  | Query(Coins.coins);

let component = ReasonReact.reducerComponent("ContentContainer");

let make = (_children) => {
  ...component,
  didMount: self => {
    Coins.request("http://localhost:3000/coins", (c) => self.send(Query(c)))
    |> ignore;
  },
  initialState: () => {coins:  []},
  reducer: (action, _state) =>
    switch (action) {
    | Query(cs) => ReasonReact.Update({coins: cs})
    },
  render: self => {
    <ContentView coins={self.state.coins} />;
  },
};