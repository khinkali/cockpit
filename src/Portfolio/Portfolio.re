type state = {empty: int};

type action =
  | TransformMenuAction;

let component = ReasonReact.reducerComponent("Portfolio");

let make = _children => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (action, _state: state) => 
  switch (action) {
  | TransformMenuAction => {
    /*let menu = Webapi.Dom.Document.getElementById*/
    ReasonReact.NoUpdate;
  }
  },
  render: _self =>
    <div className="portfolio-container">
      <CoinAdder succeeded=(a => ()) />

        /* <a
          id="menu"
          onClick=(_=> ())
          className="menu-btn mdc-elevation--z4">
          <i className="fas fa-align-justify fa-2x" />
        </a> */
      </div>,
};