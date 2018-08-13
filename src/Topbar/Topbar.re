type state = {empty: int};

type action =
  | Nothing;

let component = ReasonReact.reducerComponent("Topbar");

let make = (~click: 'a => unit, _children) => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: _self =>
    <div className="topbar-container">
      <section className="topbar-menu">
        <LinkRipple click cssClass="topbar-navi-menu" color="">
          ...<i className="fas fa-bars fa-2x" />
        </LinkRipple>
      </section>
    </div>,
};