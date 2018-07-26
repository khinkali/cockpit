type state = {empty: string};

type action =
  | Nothing;

let sidebarContainer = "sidebar-container";
let sidebarContainerMobile = "sidebar-container sidebar-menu-on-mobile";

let component = ReasonReact.reducerComponent("Sidebar");

let isOnMobile =
  Webapi.Dom.Window.matchMedia("(max-width: 1088px)", Webapi.Dom.window)
  |> MediaQuery.matches;

let make = (~menuOnMobilePressed: bool, _children) => {
  ...component,
  initialState: () => {empty: ""},
  reducer: (action: action, state: state) => ReasonReact.NoUpdate,
  render: _self => {
    <aside className=(isOnMobile && menuOnMobilePressed  ? sidebarContainerMobile : sidebarContainer) />
  }
};