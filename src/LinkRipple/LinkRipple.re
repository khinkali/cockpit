let component = ReasonReact.statelessComponent("LinkRipple");

let make = (~click: 'a => unit, ~cssClass: string, ~color: string, children) => {
  /*
   * Determine the coordinates for ripple effect
   * At the end, it will execute the click function
   */

  let onLinkClicked = e => {
    let dom = External.convertToDomElement(e->ReactEvent.Mouse.target);
    let rect = Webapi.Dom.Element.getBoundingClientRect(dom);

    let x = ReactEvent.Mouse.pageX(e) - Webapi.Dom.DomRect.left(rect);
    let y = ReactEvent.Mouse.pageY(e) - Webapi.Dom.DomRect.top(rect);

    let rippleDiv =
      Webapi.Dom.Document.createElement("div", Webapi.Dom.document);
    let domTokenList = Webapi.Dom.Element.classList(rippleDiv);

    Webapi.Dom.DomTokenList.add("ripple", domTokenList);
    Webapi.Dom.Element.setAttribute(
      "style",
      "top:" ++ string_of_int(y) ++ "px; left:" ++ string_of_int(x) ++ "px;",
      rippleDiv,
    );
    Webapi.Dom.Element.appendChild(rippleDiv, dom);

    click(());

    Js.Global.setTimeout(
      () => Webapi.Dom.Element.removeChild(rippleDiv, dom) |> ignore,
      500,
    )
    |> ignore;
  };

  {
    ...component,
    render: _self =>
      <a onClick=onLinkClicked className=cssClass> children </a>,
  };
};