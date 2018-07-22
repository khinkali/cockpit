type state = {menuOnMobil: bool};

type action =
  | ShowMenuOnMobil(bool);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {menuOnMobil: false},
  reducer: (action: action, _state: state) => switch (action) {
  | ShowMenuOnMobil(toggler) => ReasonReact.Update({menuOnMobil: toggler})
  },
  render: self =>
    <div className="app-container">
      <Sidebar />
      <div className="main-container"> 
        <Topbar />
        <Portfolio showMenu=(toggler => self.send(ShowMenuOnMobil(toggler))) /> 
        </div>
    </div>,
};

let default = ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));