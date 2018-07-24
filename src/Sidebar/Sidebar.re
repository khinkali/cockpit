type state = {empty: int};

type action =
  | None;

let component = ReasonReact.reducerComponent("Sidebar");


let fadeInOnMobil = (togglerPressed) => {
  let mql = Webapi.Dom.Window.matchMedia("(max-width: 1088px)", Webapi.Dom.window);
  let isMobile = togglerPressed && MediaQuery.matches(mql);
}

let make = (~showMenuOnMobile: bool, _children) => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: _self => {

    fadeInOnMobil(showMenuOnMobile);
    <aside className="sidebar-container" />;
  },
};