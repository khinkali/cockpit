type state = {
  empty: int,
};

type action =
  | Nothing;


let component = ReasonReact.reducerComponent("Topbar");

let make = (_children) => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: _self => {
    <div className="topbar-container">
    </div>
  }
};

   