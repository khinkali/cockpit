type state = {
  adder: bool,
  newCoin: Coins.coin,
  currencies: Coins.currencies
};

type action =
  | AddAmt(int)
  | AddCurr(string)
  | FetchCurr(Coins.currencies);

let component = ReasonReact.reducerComponent("CoinAdder");

let determineBtnState = (c: Coins.coin) =>
  if (c.amount == 0 || c.currency == "") {
    false;
  } else {
    true;
  };

let make = (~value: int => unit, _children) => {

  let handleKeyDown = evt => {
    if (ReactEventRe.Keyboard.keyCode(evt) == 69) {
      ReactEventRe.Keyboard.preventDefault(evt);
    };
    ();
  };

  let handleKeyUp = evt =>
    value(
      ReactDOMRe.domElementToObj(ReactEventRe.Keyboard.target(evt))##value,
    );

  {
  ...component,
  initialState: () => {
    adder: false,
    newCoin: {
      amount: 0,
      currency: "",
    },
    currencies: [||]
  },
  didMount: self => {
    Coins.getCurrencies(currs => self.send(FetchCurr(currs)))
    |> ignore;
  },
  reducer: (action, state) =>
    switch (action) {
    | AddAmt(v) =>
      ReasonReact.Update({
        ...state,
        adder: determineBtnState(state.newCoin),
        newCoin: {
          amount: v,
          currency: state.newCoin.currency,
        },
      })
    | AddCurr(v) =>
      ReasonReact.Update({
        ...state,
        adder: determineBtnState(state.newCoin),
        newCoin: {
          amount: state.newCoin.amount,
          currency: v,
        },
      })
    | FetchCurr(currs) => ReasonReact.Update({...state, currencies: currs})  
    },
  render: self => {
      
      let currEle = (idx, curr) =>
        <option key=("cu" ++ string_of_int(idx)) value=curr>
          (ReasonReact.string(curr))
        </option>;


      <div className="field is-horizontal">
        <div className="field-label is-normal">
          <label className="label">{ReasonReact.string("Add coin:")}</label>
        </div>

        <div className="field-body">

          <div className="field">
            <div className="control">
              <input
              placeholder="Amount"
              type_="number"
              className="input"
              step=0.0001
              onKeyUp=handleKeyUp
              onKeyDown=handleKeyDown />
            </div>
          </div>

          <div className="field">
            <div className="control">
              <div className="select">
                <select defaultValue="">
                  <option disabled=true value=""/>
                  (
                    self.state.currencies
                    |. Belt.Array.mapWithIndex(currEle)
                    |> ReasonReact.array
                  )
                </select>
              </div>
            </div>
          </div>
        </div>
      </div>
    },
  };
};