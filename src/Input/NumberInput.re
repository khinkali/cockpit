let component = ReasonReact.statelessComponent("NumberInput");

let allowedCharCodes = [48, 49, 50, 51, 52, 53, 54, 55, 56, 57];

let make = (~name: string, ~value: string => unit, ~maxLength: int, _children) => {
  /*
   * Generate side effect. Return unit. 
   */
  let handleInputValue = evt => {
    let charCode = ReactEventRe.Keyboard.charCode(evt);
    if (charCode != 0) {
      if (! List.mem(charCode, allowedCharCodes)) {
        ReactEventRe.Keyboard.preventDefault(evt);
      } else {
        value(ReactDOMRe.domElementToObj(ReactEventRe.Keyboard.target(evt))##value);
      };
    };
    ();
  };
  {
    ...component,
    render: _self =>
      <input type_="text" maxLength name onKeyPress=handleInputValue />,
  };
};