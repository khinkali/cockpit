
type state = {
  empty: int,
};

type action =
  | Nothing;


let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: _self => {
  <div className="app-container">
    <Sidebar />
    <div className="main-container">
      <Topbar />
    </div>
  </div>
  },
};

let default = ReasonReact.wrapReasonForJs(
  ~component,
  (_jsProps) => make([||])
);

   