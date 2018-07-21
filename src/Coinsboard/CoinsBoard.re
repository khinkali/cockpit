type state = {coins: Coins.coins};

type action =
  | UpdateCoins(Coins.coins)
  | FetchCoins;

let component = ReasonReact.reducerComponent("CoinsBoard");

let make = _children => {
  ...component,
  initialState: () => {coins: [||]},
  didMount: self => self.send(FetchCoins),
  reducer: (action, _state) =>
    switch (action) {
    | UpdateCoins(a) => ReasonReact.Update({coins: a})
    | FetchCoins =>
      ReasonReact.SideEffects(
        (self => Coins.get(c => self.send(UpdateCoins(c))) |> ignore),
      )
    },
  render: self =>
    <Fragment>
      <CoinsTable coins=self.state.coins />
      <CoinAdder
        succAdded=(_msg => self.send(FetchCoins))
        errAdded=(_e => ())
      />
    </Fragment>,
};