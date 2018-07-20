type state = {empty: int};

type action =
  | TransformMenuAction
  | MenuToggler;

let component = ReasonReact.reducerComponent("Portfolio");

let make = _children => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (action, _state: state) =>
    switch (action) {
    | TransformMenuAction =>
      switch (
        Webapi.Dom.Document.getElementById(
          "portfolio-menu",
          Webapi.Dom.document,
        )
      ) {
      | None =>
        ReasonReact.SideEffects(
          (
            _self =>
              raise(
                Element.NotFound(
                  "Can not find element with the id portfolio-menu.",
                ),
              )
          ),
        )
      | Some(e) =>
        ReasonReact.SideEffects(
          (
            _self =>
              e
              |> Webapi.Dom.Element.classList
              |> DomTokenListRe.add("menu-btn-active")
          ),
        )
      }
    },
  render: self =>
    <div className="portfolio-container">
      /* <CoinAdder succeeded=(a => ()) /> */

        <a
          id="portfolio-menu"
          onClick=(_ => self.send(TransformMenuAction))
          className="menu-btn mdc-elevation--z4">
          <i className="fas fa-align-justify fa-2x" />
        </a>
      </div>,
};