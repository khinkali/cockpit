type state = {empty: int};

type action =
  | Nothing;

let component = ReasonReact.reducerComponent("Topbar");

let make = _children => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: _self =>
    <div className="topbar-container">
      <a className="topbar-menu-on-mobile mdc-ripple-surface mdc-ripple-radius-bounded">
        <i className="fas fa-bars fa-2x"></i>
      </a>
    </div>,
};