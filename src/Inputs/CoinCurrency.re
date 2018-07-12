type mdcSelectCl;

[@bs.new] [@bs.module "@material/select"]
external mdcSelect : Dom.element => mdcSelectCl = "MDCSelect";

type state = {currs: Coins.currencies};

type action =
  | SelectedCurr(string)
  | FetchCurr(Coins.currencies);

let component = ReasonReact.reducerComponent("CoinCurrecy");

let make = _children => {
  ...component,
  initialState: () => {currs: [||]},
  didMount: self => {
    Coins.getCurrencies(currs => self.send(FetchCurr(currs)));
    
    let currEle = Webapi.Dom.document |> DocumentRe.getElementById("coin-curr-select");

    let _ =
      switch (currEle) {
      | Some(a) => mdcSelect(a)
      | None => raise(Element.NotFound("Can not find the element"))
      };

    ();
    
  },
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

      <div className="mdc-select mdc-select--box" id="coin-curr-select">
        <select className="mdc-select__native-control">
          <option value="" disabled=true selected=true></option>
          <option value="ETH">
            {ReasonReact.string("ETH")}
          </option>
          <option value="XRP">
            {ReasonReact.string("XRP")}
          </option>
          <option value="BTC">
             {ReasonReact.string("BTC")}
          </option>
        </select>
        <label className="mdc-floating-label">{ReasonReact.string("Select a value!")}</label>
        <div className="mdc-line-ripple"></div>
      </div>

    /*<div className="mdc-select">
      <select className="mdc-select__native-control">
        <option value="" disabled=true selected=true></option>
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
    </div>;*/



  },
};