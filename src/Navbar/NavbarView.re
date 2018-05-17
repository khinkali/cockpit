
/* Import SideBar logos */
[%%raw "import ovLogo from './Assets/Overview.svg'"];
[%%raw "import stockLogo from './Assets/Stocks.svg'"];
let ovLogo' = [%raw "ovLogo"];
let stockLogo' = [%raw "stockLogo"];
let component = ReasonReact.statelessComponent("NavbarView");


let make = (_children) => {
  ...component,
  render: _self => {
  <nav className="navbar navbar-expand-lg fixed-top" id="mainNav">
    <a className="navbar-brand" href="#">{ReasonReact.string("Logo")}</a>
    <NavbarTogglerView />
    
    <div className="collapse navbar-collapse" id="navbarToggler">
      <ul className="navbar-nav navbar-sidenav">
        <NavItemView id="navItemDashboard" text="Overview" active=NavItem.Dashboard>
          ...<img src={ovLogo'} height="40" width="40"/>
        </NavItemView>
        <NavItemView id="navItemStock" text="Stocks" active=NavItem.Stock>
          ...<img src={stockLogo'} height="40" width="40"/>
        </NavItemView>
      </ul>
      <SidebarTogglerView />
    </div>
  </nav>
  }
};