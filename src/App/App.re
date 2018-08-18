type state = {showMenuOnMobile: bool};

type action =
  | ShowMenuOnMobile(bool);

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {showMenuOnMobile: false},
  reducer: (action: action, _state: state) =>
    switch (action) {
    | ShowMenuOnMobile(toggler) =>
      ReasonReact.Update({showMenuOnMobile: !toggler});
    },
  render: self =>
    <div className="app-container">
      <Topbar
        onClick={
          (mobile) => Js.log(string_of_bool(mobile))
        }
      />
      /* <Navigation showMobile={self.state.showMenuOnMobile} /> */
    </div>,
};

let default = ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));