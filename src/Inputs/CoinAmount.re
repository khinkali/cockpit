type mdcTextFieldCl;

[@bs.new] [@bs.module "@material/textfield"]
external mdcTextField : Dom.element => mdcTextFieldCl = "MDCTextField";

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
    didMount: _self => {
      let coinEle =
        Webapi.Dom.document |> DocumentRe.getElementById("coin-amt-box");

      let _ =
        switch (coinEle) {
        | Some(a) => mdcTextField(a)
        | None => raise(Element.NotFound("Can not find the element"))
        };
      ();
    },
    render: _self =>
      <div className="mdc-text-field mdc-text-field--box" id="coin-amt-box">
          <input
          type_="number"
          className="mdc-text-field__input"
          id="coin-amt-input" 
          step=0.0001
          onKeyUp=handleKeyUp
          onKeyDown=handleKeyDown
        />
      <label className="mdc-floating-label" htmlFor="coin-amt-input">{ReasonReact.string("Amount")}</label>
      <div className="mdc-line-ripple"></div>
      </div>
  };
};