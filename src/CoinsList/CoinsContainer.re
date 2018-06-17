type state = {
  coins: Coins.coins,
  newCoin: Coins.coin
};

type action =
  | Query(Coins.coins)
  | AddAmount(string);

let component = ReasonReact.reducerComponent("CoinsContainer");

let make = _children => {
  ...component,
  initialState: () => {coins: [], newCoin: {amount: 0, currency: ""}},
  didMount: self => Coins.get(c => self.send(Query(c))) |> ignore,
  reducer: (action, state) =>
    switch (action) {
    | Query(cs) => ReasonReact.Update({...state, coins: cs})
    | AddAmount(amt) =>
      Js.log(amt); 
      ReasonReact.NoUpdate
    },
  render: self =>
    <Fragment>
      <CoinsList coins=self.state.coins />
      <NumberInput name="amount" value=(v => self.send(AddAmount(v))) maxLength=5/>
    </Fragment>,
};