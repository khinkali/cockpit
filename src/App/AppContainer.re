%raw "import './scss/app.scss'";

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
    <Fragment>
      <TopbarContainer />
      <ContentContainer>
        <SidebarContainer />
        <main>{ReasonReact.string("Hello")}</main>
      </ContentContainer>
    </Fragment>
  },
};

let default = ReasonReact.wrapReasonForJs(
  ~component,
  (_jsProps) => make([||])
);

   