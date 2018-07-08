type state = {
  btnState: bool,
  newCoin: Coins.coin,
};

type action =
  | AddAmt(int)
  | AddCurr(string);

let component = ReasonReact.reducerComponent("CoinAdder");

let determineBtnState = (c: Coins.coin) =>
  if (c.amount == 0 || c.currency == "") {
    false;
  } else {
    true;
  };

let make = _children => {
  ...component,
  initialState: () => {
    btnState: false,
    newCoin: {
      amount: 0,
      currency: "",
    },
  },
  reducer: (action, state) =>
    switch (action) {
    | AddAmt(v) =>
      ReasonReact.Update({
        btnState: determineBtnState(state.newCoin),
        newCoin: {
          amount: v,
          currency: state.newCoin.currency,
        },
      })
    | AddCurr(v) =>
      ReasonReact.Update({
        btnState: determineBtnState(state.newCoin),
        newCoin: {
          amount: state.newCoin.amount,
          currency: v,
        },
      })
    },
  render: self =>
    <Fragment> <CoinAmount value=(v => self.send(AddAmt(v))) /> 
    <CoinCurrency />
    </Fragment>,
};