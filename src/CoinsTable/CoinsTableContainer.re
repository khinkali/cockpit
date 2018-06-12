type state = {
  newCoin: Coins.coin,
  coins: Coins.coins,
};

type action =
  | AddAmt(string)
  | AddCurr(string)
  | Query(Coins.coins);

let component = ReasonReact.reducerComponent("CoinsTableContainer");

let make = _children => {
  ...component,
  initialState: () => {
    newCoin: {
      amount: 0,
      currency: "",
    },
    coins: [],
  },
  didMount: self => Coins.get(c => self.send(Query(c))) |> ignore,
  reducer: (action, state) =>
    switch (action) {
    | AddAmt(value) =>
      ReasonReact.Update({
        ...state,
        newCoin: {
          ...state.newCoin,
          amount: int_of_string(value),
        },
      })
    | AddCurr(value) =>
      ReasonReact.Update({
        ...state,
        newCoin: {
          ...state.newCoin,
          currency: value,
        },
      })
    | Query(cs) => ReasonReact.Update({...state, coins: cs})
    },
  render: self =>
    <CoinsTableView
      coins=self.state.coins
      amountEvent=(v => self.send(AddAmt(v)))
      currEvent=(v => self.send(AddCurr(v)))
      submitCoin=(() => ()) 
    />,
};