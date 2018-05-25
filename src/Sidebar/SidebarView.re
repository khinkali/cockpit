let component = ReasonReact.statelessComponent("SidebarView");

let make = (_children) => {
  ...component,
  render: _self => {

    let iconEle = (icon: string) 
                => ReasonReact.cloneElement(
                  <i className="material-icons mdc-list-item__graphic">{ReasonReact.string(icon)}</i>,
                  ~props={"aria-hidden": true},
                  [||]
                );

    <aside className="mdc-drawer mdc-drawer--permanent mdc-typography">
      <nav className="mdc-drawer__drawer">
        <header className="mdc-drawer__header">
          <div className="mdc-drawer__header-content">
            {ReasonReact.string("Header")}
          </div>
        </header>
        <nav id="icon-with-text-demo" className="mdc-drawer__content mdc-list">
          <a className="mdc-list-item mdc-list-item--activated" href="#">
            {iconEle("inbox")}
            {ReasonReact.string("Inbox")}
          </a>
          <a className="mdc-list-item" href="#">
            {iconEle("start")}
            {ReasonReact.string("Inbox")}
          </a>
        </nav>
      </nav>
    </aside>
  }
};