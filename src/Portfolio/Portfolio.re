type state = {empty: int};

type action =
  | NoUpdate;

let component = ReasonReact.reducerComponent("Portfolio");

let make = _children => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (action: action, state: state) => ReasonReact.NoUpdate,
  render: self => {

    <div className="portfolio-container">
      <CoinsBoard />
    </div>;
  },
};