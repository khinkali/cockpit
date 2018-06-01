let component = ReasonReact.statelessComponent("SidebarView");

let make = (_children) => {
  ...component,
  render: _self => {
    <nav className="mdc-drawer mdc-drawer--permanent demo-drawer">
      <div className="mdc-list-group">
        <nav className="mdc-list">
          <a className="mdc-list-item mdc-list-item--selected demo-drawer-list-item" href="#">
            <i className="material-icons mdc-list-item__graphic" ariaHidden=true>
              {ReasonReact.string("inbox")}
            </i>
              {ReasonReact.string("Inbox")}
          </a>
          <a className="mdc-list-item demo-drawer-list-item" href="#">
            <i className="material-icons mdc-list-item__graphic" ariaHidden=true>
              {ReasonReact.string("star")}
            </i>
              {ReasonReact.string("Star")}
          </a>
          <a className="mdc-list-item demo-drawer-list-item" href="#">
            <i className="material-icons mdc-list-item__graphic" ariaHidden=true>
              {ReasonReact.string("send")}
            </i>
            {ReasonReact.string("Sent Mail")}
          </a>
        </nav>

        <hr className="mdc-list-divider" />

        <nav className="mdc-list">
          <a className="mdc-list-item demo-drawer-list-item" href="#">
            <i className="material-icons mdc-list-item__graphic" ariaHidden=true>
              {ReasonReact.string("email")}
            </i>
              {ReasonReact.string("All Mail")}
          </a>
        </nav>
      </div>
    </nav>
  }
};