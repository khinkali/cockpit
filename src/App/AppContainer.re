type state = {
  empty: int,
};

type action =
  | Nothing;


let component = ReasonReact.reducerComponent("AppContainer");

let make = (_children) => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: _self => {
      <div>
        <h1>{ReasonReact.string("Hello")}</h1>
        <ContentContainer />
      </div>
  },
};

let default = ReasonReact.wrapReasonForJs(
  ~component,
  (_jsProps) => make([||])
);

   