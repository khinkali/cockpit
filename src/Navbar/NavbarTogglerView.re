let component = ReasonReact.statelessComponent("NavbarTogglerView");

let make = (_children) => {
  ...component,
  render: _self => {
    ReasonReact.cloneElement(
      <button className="navbar-toggler" _type="button" />,
      ~props={"data-toggle": "collapse", "data-target": "#navbarToggler", "aria-controls": "navbarToggler",
              "aria-expanded": "false", "aria-label": "Toggle navigation"},
      [|<span className="navbar-toggler-icon"></span>|]
    );
  }
}