type state = {
  coins: Coins.coins
};

type action =
  | Query(Coins.coins);

let component = ReasonReact.reducerComponent("ContentContainer");

let make = (_children) => {
  ...component,
  didMount: self => {

    Security.query
    |> Js.Promise.then_(x => Js.Promise.resolve(Js.log(x)));

    Coins.request((c) => self.send(Query(c)))
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