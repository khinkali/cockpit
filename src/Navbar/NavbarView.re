let component = ReasonReact.statelessComponent("NavbarView");

let make = (_children) => {
  ...component,
  render: _self => {
  <nav className="navbar navbar-expand-lg fixed-top" id="mainNav">
    <a className="navbar-brand" href="#">{ReasonReact.string("Logo")}</a>
    <NavbarTogglerView />
    
    <div className="collapse navbar-collapse" id="navbarToggler">
      <ul className="navbar-nav navbar-sidenav">
        <NavItemView text="Dashboard" href="#" icon="fa-sitemap" />
        <NavItemView text="Menu" href="#" icon="fa-dashboard" />
      </ul>
      <SidebarTogglerView />
    </div>
  </nav>
  }
};