

type state = {
  empty: int
};

type action =
  | None;

let component = ReasonReact.reducerComponent("SidebarContainer");

let make = (_children) => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: (_self) => {
    <SidebarView />
  }
};
