let eleNaviMobile = "navi-mobile";

type state = {empty: int};

type action =
  | Nothing;

let component = ReasonReact.reducerComponent("Navigation");

let toggleMenuMobile =
    (
      ele: option(Dom.element),
      editTokenList: Webapi.Dom.DomTokenList.t => unit,
    ) =>
  switch (ele) {
  | None =>
    raise(
      Element.NotFound("Element " ++ eleNaviMobile ++ " is not available."),
    )
  | Some(e) => e |> Webapi.Dom.Element.classList |> editTokenList
  };

let handleMenuOnMobile = (show: bool) =>
  show ?
    toggleMenuMobile(
      Webapi.Dom.Document.getElementById(eleNaviMobile, Webapi.Dom.document),
      e =>
      Webapi.Dom.DomTokenList.add("navi-show-on-mobile", e)
    ) :
    toggleMenuMobile(
      Webapi.Dom.Document.getElementById(eleNaviMobile, Webapi.Dom.document),
      e =>
      Webapi.Dom.DomTokenList.remove("navi-show-on-mobile", e)
    );

let make = (~showMobile: bool, _children) => {
  ...component,
  initialState: () => {empty: 0},
  didMount: _self => Js.log("Mountet"),
  didUpdate: _oldNewSelf => handleMenuOnMobile(showMobile),
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: _self => {
    Js.log("Inside navigation");
    <div className="navi-container" id="navi-mobile">
      <section className="navi-menu">
        <LinkRipple
          click={(_e) => Js.log("Clicked")} cssClass="navi-link" color="">
          ...{ReasonReact.string("DASHBOARD")}
        </LinkRipple>
        <LinkRipple
          click={(_e) => Js.log("Clicked")}
          cssClass="navi-link navi-link-active"
          color="">
          ...{ReasonReact.string("COINS")}
        </LinkRipple>
      </section>
    </div>;
  },
};