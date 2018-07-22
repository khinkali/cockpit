type state = {
  menuToggler: bool,
  menuIconStyle: string,
  menuActionStyle: string,
};

let menuIdEle = "portfolio-menu";
let menuInactive = "menu-btn mdc-elevation--z4";
let menuActive = "menu-btn menu-btn-active mdc-elevation--z4";
let iconInactive = "fa-align-justify";
let iconActive = "fa-times";

let getMobilMenuEle = eleName =>
  Webapi.Dom.Document.getElementById(eleName, Webapi.Dom.document);

let toggleMobilIcon = icon => icon == iconInactive ? iconActive : iconInactive;

let toggleMobilAction = style =>
  style == menuInactive ? menuActive : menuInactive;

type action =
  | MenuToggler;

let component = ReasonReact.reducerComponent("Portfolio");

let make = (~showMenu: bool => unit, _children) => {
  ...component,
  initialState: () => {
    menuToggler: false,
    menuIconStyle: iconInactive,
    menuActionStyle: menuInactive,
  },
  didMount: _self =>
    (
      if (getMobilMenuEle(menuIdEle) == None) {
        Element.NotFound("Can not find element with the id portfolio-menu.");
        ();
      }
    )
    |> ignore,
  reducer: (action, state: state) =>
    switch (action) {
    | MenuToggler =>
      switch (getMobilMenuEle(menuIdEle)) {
      | None => ReasonReact.NoUpdate
      | Some(a) =>
        ReasonReact.UpdateWithSideEffects(
          {
            menuToggler: ! state.menuToggler,
            menuIconStyle: toggleMobilIcon(state.menuIconStyle),
            menuActionStyle: toggleMobilAction(state.menuActionStyle),
          },
          (self => showMenu(self.state.menuToggler)),
        )
      }
    },
  render: self =>
    <div className="portfolio-container">
      <CoinsBoard />
      <a
        id=menuIdEle
        onClick=(_ => self.send(MenuToggler))
        className=self.state.menuActionStyle>
        <i className=("fas " ++ self.state.menuIconStyle ++ " fa-2x") />
      </a>
    </div>,
};