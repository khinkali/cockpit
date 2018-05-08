[%%raw "import './Styles/navbar.css'"];

type state = {
  empty: int,
};

type action =
  | Nothing;


let component = ReasonReact.reducerComponent("NavbarContainer");

let make = (_children) => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: _self => {
    <NavbarView />
  },
};