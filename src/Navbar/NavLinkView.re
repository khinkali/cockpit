let component = ReasonReact.statelessComponent("NavLinkView");

let make = (~linkText: string, ~href: string, _children) => {
  ...component,
  render: (_self) => {
    <li className="nav-item">
      <a className="nav-link" href={href}>
        <i className="fa fa-fw fa-dashboard"></i>
        <span className="nav-link-text">{ReasonReact.string(linkText)}</span>
      </a>
    </li>
  }
};