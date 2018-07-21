type state = {menuToggler: bool};

type action =
  | MenuToggler;

let component = ReasonReact.reducerComponent("Portfolio");

let make = _children => {
  ...component,
  initialState: () => {menuToggler: false},
  reducer: (action, _state: state) =>
    switch (action) {
    | MenuToggler =>
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
  render: _self =>
    <div className="portfolio-container">
      
      <CoinsBoard />
      /*   <a
          id="portfolio-menu"
          onClick=(_ => self.send(MenuToggler))
          className="menu-btn mdc-elevation--z4">
          <i className="fas fa-align-justify fa-2x" />
        </a> */
      </div>,
};