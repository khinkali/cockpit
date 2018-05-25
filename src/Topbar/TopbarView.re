let component = ReasonReact.statelessComponent("TopbarView");

let make = (_children) => {
  ...component,
  render: (_self) => {
  <header className="mdc-top-app-bar">
    <div className="mdc-top-app-bar__row">
      <section className="mdc-top-app-bar__section mdc-top-app-bar__section--align-start">
        <a href="#" className="material-icons mdc-top-app-bar__navigation-icon">{ReasonReact.string("Menu")}</a>
        <span className="mdc-top-app-bar__title">{ReasonReact.string("Title")}</span>
      </section>
    </div>
  </header>
  }
};