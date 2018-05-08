let component = ReasonReact.statelessComponent("NavItemView");

let make = (~text: string, ~href: string, ~icon: string, _children) => {
  ...component,
  render: (_self) => {
    <li className="nav-item">
      <a className="nav-link" href={href}>
        <i className=("fa fa-fw " ++ icon)></i>
        <span className="nav-link-text">{ReasonReact.string(text)}</span>
      </a>
    </li>
  }
};