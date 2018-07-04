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
      <div className="mdc-text-field">
        <input
          type_="number"
          className="mdc-text-field__input"
          id="amount-field"
          step=0.0001
          onKeyUp=handleKeyUp
          onKeyDown=handleKeyDown
        />
        <label className="mdc-floating-label" htmlFor="amount-field">
          {ReasonReact.string("Hint text")}
        </label>
        <div className="mdc-line-ripple" />
      </div>,
  };
};