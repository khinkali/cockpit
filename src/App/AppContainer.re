

%raw "import './app.scss'";
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
      /*<div className="d-flex flex-row wrapper">
        <div className="sidebar">
          {ReasonReact.string("Sidebar")}
        </div>
        <div className="container-fluid">
          {ReasonReact.string("Content")}
        </div>
        <button className="circle-btn">
        </button>
      </div>*/
      <ContentContainer />
  },
};

let default = ReasonReact.wrapReasonForJs(
  ~component,
  (_jsProps) => make([||])
);

   