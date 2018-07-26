type state = {showMenuOnMobile: bool};

type action =
  | ShowMenuOnMobile(bool);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {showMenuOnMobile: false},
  reducer: (action: action, _state: state) => switch (action) {
  | ShowMenuOnMobile(toggler) => ReasonReact.Update({showMenuOnMobile: toggler})
  },
  render: self =>
    <div className="app-container">
      <Sidebar menuOnMobilePressed=self.state.showMenuOnMobile />
      <div className="main-container"> 
        <Topbar />
        <Portfolio showMenu=(toggler => self.send(ShowMenuOnMobile(toggler))) /> 
        </div>
    </div>,
};

let default = ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));