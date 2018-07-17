type state = {empty: int};

type action =
  | Nothing;

let component = ReasonReact.reducerComponent("Portfolio");

let make = _children => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: _self =>
    <div className="portfolio-container">
      /* <CoinAdder succeeded=(a => ()) /> */

        <a href="#" className="show-menu-btn mdc-elevation--z4">
          <i className="fas fa-align-justify fa-2x" />
        </a>
      </div>,
};