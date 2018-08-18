let eleNaviMobile = "navi-mobile";

type state = {empty: int};

type action =
  | Nothing;

let component = ReasonReact.reducerComponent("Navigation");

let make = (~showMobile: bool, _children) => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: _self => {
    <div className="navi-container" id="navi-mobile">
      <section className="navi-menu">
      </section>
    </div>;
  },
};