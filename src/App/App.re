
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
    <Fragment>
      <Portfolio />
    </Fragment>
  },
};

let default = ReasonReact.wrapReasonForJs(
  ~component,
  (_jsProps) => make([||])
);

   