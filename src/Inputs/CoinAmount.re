

let component = ReasonReact.statelessComponent("CoinAmount");

let make = (~value: int => unit, _children) => {
  /*
     Prevent typing e into the filed.
   */
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
    render: _self =>
    <div className="mdc-text-field mdc-text-field--outlined" id="coin-amount-input">
      <input
          type_="number"
          className="mdc-text-field__input"
          id="amount-field"
          step=0.0001
          onKeyUp=handleKeyUp
          onKeyDown=handleKeyDown
        />
      <label className="mdc-floating-label" htmlFor="amount-field">
            {ReasonReact.string("Amount")}
          </label>
      <div className="mdc-notched-outline">
        <svg>
          <path className="mdc-notched-outline__path"/>
        </svg>
      </div>
      <div className="mdc-notched-outline__idle"></div>
    </div>
  };
};