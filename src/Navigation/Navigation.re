/* Link identification */
let dashboard = "DASHBOARD";
let coins = "COINS";

type state = {activeState: string};

type action =
  | ActiveLink(string);

let component = ReasonReact.reducerComponent("Navigation");

let make = (~showMobile: bool, _children) => {
  let setActiveState = (evt, self) => Js.log(self.ReasonReact.state);
  /*self.send(ActiveLink(ReactEvent.Mouse.target(evt)##id));*/
  {
    ...component,
    initialState: () => {activeState: ""},
    reducer: (action: action, state: state) =>
      switch (action) {
      | ActiveLink(_id) =>
        ReasonReact.Update({activeState: "navi-link-active"})
      },
    render: self =>
      <nav className="navi-container">
        <div className="navi-menu">
          <a
            id=dashboard
            onClick={self.handle(setActiveState)}
            className={self.state.activeState}>
            {ReasonReact.string(dashboard)}
          </a>
          <a id=coins onClick={self.handle(setActiveState)}>
            {ReasonReact.string(coins)}
          </a>
        </div>
      </nav>,
  };
};