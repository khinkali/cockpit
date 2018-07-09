type state = {currs: Coins.currencies};

type action =
  | SelectedCurr(string)
  | FetchCurr(Coins.currencies);

let component = ReasonReact.reducerComponent("CoinCurrecy");

let make = _children => {
  ...component,
  initialState: () => {currs: [||]},
  didMount: self =>
    Coins.getCurrencies(currs => self.send(FetchCurr(currs))) |> ignore,
  reducer: (action, _state) =>
    switch (action) {
    | SelectedCurr(_curr) => ReasonReact.NoUpdate
    | FetchCurr(currs) => ReasonReact.Update({currs: currs})
    },
  render: self => {
    let currOptions = (idx, curr) =>
      <option key=("cu" ++ string_of_int(idx)) value=curr>
        (ReasonReact.string(curr))
      </option>;

    <div className="mdc-select mdc-select--box">
      <select className="mdc-select__native-control">
        (
          self.state.currs
          |. Belt.Array.mapWithIndex(currOptions)
          |> ReasonReact.array
        )
      </select>
      <label className="mdc-floating-label">
        (ReasonReact.string("Select currency"))
      </label>
      <div className="mdc-line-ripple" />
    </div>;
  },
};