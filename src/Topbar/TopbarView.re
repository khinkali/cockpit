let component = ReasonReact.statelessComponent("TopbarView");

let make = (_children) => {
  ...component,
  render: (_self) => {
  <header className="mdc-top-app-bar mdc-top-app-bar--fixed">
    <div className="mdc-top-app-bar__row">
      <section className="mdc-top-app-bar__section mdc-top-app-bar__section--align-start">
        <a href="#" className="material-icons mdc-top-app-bar__navigation-icon">{ReasonReact.string("menu")}</a>
        <span className="mdc-top-app-bar__title">{ReasonReact.string("Title")}</span>
      </section>
      <section className="mdc-top-app-bar__section mdc-top-app-bar__section--align-end" role="toolbar">
        <a href="#" className="material-icons mdc-top-app-bar__action-item" ariaLabel="Download" alt="Download">{ReasonReact.string("file_download")}</a>
        <a href="#" className="material-icons mdc-top-app-bar__action-item" ariaLabel="Print this page" alt="Print this page">{ReasonReact.string("print")}</a>
        <a href="#" className="material-icons mdc-top-app-bar__action-item" ariaLabel="Bookmark this page" alt="Bookmark this page">{ReasonReact.string("bookmark")}</a>
      </section>
    </div>
  </header>
  }
};