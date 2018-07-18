type state = {empty: int};

type action('a) =
  | TransformMenuAction('a)
  | Nothing;

let component = ReasonReact.reducerComponent("Portfolio");

let make = _children => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: _self =>
    <div className="portfolio-container">
      /* <CoinAdder succeeded=(a => ()) /> */

        <a
          onClick=(evt => ())
          className="menu-btn menu-initial-state mdc-elevation--z4">
          <i className="fas fa-align-justify fa-2x" />
        </a>
      </div>,
};