let component = ReasonReact.statelessComponent("NavItemView");

let make = (~id: string, ~text: string, ~active: NavItem.active, children) => {
  let onClick = (_event, _self)  => {
    active;
    ();
  };
  {
    ...component,
    render: (self) => {

      let activeClass = "nav-item";

      <li className={activeClass} id=id>
        <a className="nav-link" onClick={self.handle(onClick)}>
          {children}
          <span className="pl-3 nav-link-text">{ReasonReact.string(text)}</span>
        </a>
      </li>;
    }
  }
};