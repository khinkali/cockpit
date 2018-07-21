external convertErrMsg : Js.Promise.error => string = "%identity";

type state = {
  adder: bool,
  amtMask: string,
  newCoin: Coins.coin,
  currencies: Coins.currencies,
};

type action('a) =
  | AddAmt(float)
  | AddCurr(string)
  | AddSucc(string)
  | AddErr('a)
  | FetchCurr(Coins.currencies);

let component = ReasonReact.reducerComponent("CoinAdder");

let isGreaterZero = (c: Coins.coin) =>
  if (c.amount <= 0.0 || c.currency == "") {
    true;
  } else {
    false;
  };

let handleKeyDown = evt => {
  if (ReactEventRe.Keyboard.keyCode(evt) == 69) {
    ReactEventRe.Keyboard.preventDefault(evt);
  };
  ();
};

let convertStringToX =
    (value: string, converter: string => 'a, default: 'a)
    : 'a =>
  if (String.length(value) == 0) {
    default;
  } else {
    converter(value);
  };

let make = (~succAdded: string => unit, ~errAdded: string => unit, _children) => {
  ...component,
  initialState: () => {
    adder: true,
    amtMask: "",
    newCoin: {
      amount: 0.0,
      currency: "",
    },
    currencies: [||],
  },
  didMount: self => {
    Coins.fetchCurrs(currs => self.send(FetchCurr(currs))) |> ignore
  },
  reducer: (action, state) =>
    switch (action) {
    | AddAmt(v) =>
      let newValue: Coins.coin = {
        amount: v,
        currency: state.newCoin.currency,
      };

      ReasonReact.Update({
        ...state,
        amtMask: UtilWrapper.parseFloatToString(v),
        adder: isGreaterZero(newValue),
        newCoin: newValue,
      });
    | AddCurr(v) =>
      let newValue: Coins.coin = {amount: state.newCoin.amount, currency: v};

      ReasonReact.Update({
        ...state,
        adder: isGreaterZero(newValue),
        newCoin: newValue,
      });
    | FetchCurr(currs) => ReasonReact.Update({...state, currencies: currs})
    | AddSucc(a) =>
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          adder: true,
          newCoin: {
            amount: 0.0,
            currency: "",
          },
        },
        (_self => succAdded(a)),
      )

    | AddErr(a) => ReasonReact.SideEffects(_self => errAdded(convertErrMsg(a)))
    },
  render: self => {
    let currEle = (idx, curr) =>
      <option key=("cu" ++ string_of_int(idx)) value=curr>
        (ReasonReact.string(curr))
      </option>;

    <Fragment>
      <div className="field is-horizontal">
        <div className="field-label is-large">
          <label className="label"> (ReasonReact.string("Add coin:")) </label>
        </div>
        <div className="field-body">
          <div className="field">
            <div className="control">
              <input
                required=true
                placeholder="Amount"
                type_="number"
                className="input is-large"
                min=0
                step=0.0001
                value=self.state.amtMask
                onChange=(
                  evt => {
                    let amt =
                      convertStringToX(
                        Event.valueFromForm(evt),
                        float_of_string,
                        0.0,
                      );
                      self.send(AddAmt(amt));
                  }
                )
                onKeyDown=handleKeyDown
              />
            </div>
          </div>
          <div className="field">
            <div className="control">
              <div className="select is-large">
                <select
                  value=self.state.newCoin.currency
                  onChange=(
                    evt => self.send(AddCurr(Event.valueFromForm(evt)))
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
                onClick=(
                  _evt =>
                    Coins.post(self.state.newCoin)
                    |> Js.Promise.then_(a =>
                         Js.Promise.resolve(self.send(AddSucc(a)))
                       )
                    |> Js.Promise.catch(err =>
                         Js.Promise.resolve(self.send(AddErr(err)))
                       )
                    |> ignore
                )
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