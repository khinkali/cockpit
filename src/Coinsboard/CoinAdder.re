type state = {
  adder: bool,
  newCoin: Coins.coin,
  currencies: Coins.currencies,
};

type action =
  | AddAmt(int)
  | AddCurr(string)
  | FetchCurr(Coins.currencies);

let component = ReasonReact.reducerComponent("CoinAdder");

let isGreaterZero = (c: Coins.coin) => {
  if (c.amount <= 0 || c.currency == "") {
    true;
  } else {
    false;
  };
};

let make = _children => {
  let handleKeyDown = evt => {
    if (ReactEventRe.Keyboard.keyCode(evt) == 69) {
      ReactEventRe.Keyboard.preventDefault(evt);
    };
    ();
  };

  let valueFromKeyUpEvent = evt : int => ReactDOMRe.domElementToObj(
                                              ReactEventRe.Keyboard.target(
                                                evt,
                                              ),
                                            )##value;                                          

  let valueFromFormEvent = evt => ReactDOMRe.domElementToObj(
                                             ReactEventRe.Form.target(evt),
                                           )##value;

  {
    ...component,
    initialState: () => {
      adder: true,
      newCoin: {
        amount: 0,
        currency: "",
      },
      currencies: [||],
    },
    didMount: self =>
      Coins.getCurrencies(currs => self.send(FetchCurr(currs))) |> ignore,
    reducer: (action, state) =>
      switch (action) {
      | AddAmt(v) =>
        let newValue: Coins.coin = {
          amount: v,
          currency: state.newCoin.currency,
        };

        ReasonReact.Update({
          ...state,
          adder: isGreaterZero(newValue),
          newCoin: newValue,
        });
      | AddCurr(v) =>
        
        let newValue: Coins.coin = {
          amount: state.newCoin.amount,
          currency: v,
        };

        ReasonReact.Update({
          ...state,
          adder: isGreaterZero(newValue)  ,
          newCoin: newValue,
        });
      | FetchCurr(currs) => ReasonReact.Update({...state, currencies: currs})
      },
    render: self => {
      let currEle = (idx, curr) =>
        <option key=("cu" ++ string_of_int(idx)) value=curr>
          (ReasonReact.string(curr))
        </option>;

      <Fragment>
        <div className="field is-horizontal">
          <div className="field-label is-large">
            <label className="label">
              (ReasonReact.string("Add coin:"))
            </label>
          </div>
          <div className="field-body">
            <div className="field">
              <div className="control">
                <input
                  placeholder="Amount"
                  type_="number"
                  className="input is-large"
                  step=0.0001
                  onKeyUp=(evt => self.send(AddAmt(valueFromKeyUpEvent(evt))))
                  onInput=(evt => self.send(AddAmt(valueFromFormEvent(evt))))
                  onKeyDown=handleKeyDown
                />
              </div>
            </div>
            <div className="field">
              <div className="control">
                <div className="select is-large">
                  <select
                    defaultValue=""
                    onChange=(
                      evt => self.send(AddCurr(valueFromFormEvent(evt)))
                    )>
                    <option disabled=true value="" />
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
        <div className="field is-horizontal">
          <div className="field-label" />
          <div className="field-body">
            <div className="field">
              <div className="control">
                <button
                  className="button is-large is-primary"
                  disabled=self.state.adder>
                  (ReasonReact.string("Add"))
                </button>
              </div>
            </div>
          </div>
        </div>
      </Fragment>;
    },
  };
};