/* Link identification */
let dashboard = "DASHBOARD";
let coins = "COINS";

type linkClass = {
  dashboard: string,
  coins: string,
};

let linkClassInit = dashboard;

type state = {
  activeState: string,
  linkClass,
};

let intitState = {
  activeState: "",
  linkClass: {
    dashboard: "",
    coins: "",
  },
};

type action =
  | ActiveLink;

let component = ReasonReact.reducerComponent("Navigation");

let make = (~showMobile: bool, _children) => {
  let toggleActiveState = (evt, self) => Js.log(self.ReasonReact.state);
  /*self.send(ActiveLink(ReactEvent.Mouse.target(evt)##id));*/
  {
    ...component,
    initialState: () => intitState,
    reducer: (action: action, state: state) => ReasonReact.NoUpdate, /*switch (action) {
      | ActiveLink => ReasonReact.Update({activeState: "navi-link-bulk navi-menu-active"})
      }*/
    render: self =>
      <nav className="navi-container">
        <div className="navi-menu">
          <a className={self.state.activeState} id=dashboard onClick={self.handle(toggleActiveState)}>
            <div className={self.state.activeState} />
            {ReasonReact.string(dashboard)}
          </a>
          <a className={self.state.activeState} id=coins onClick={self.handle(toggleActiveState)}>
            <div className={self.state.activeState} />
            {ReasonReact.string(coins)}
          </a>
        </div>
      </nav>,
  };
};
