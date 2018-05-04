let component = ReasonReact.statelessComponent("NavbarView");

let make = (_children) => {
  ...component,
  render: _self => {
    let togglerButton = 
    ReasonReact.cloneElement(
      <button className="navbar-toggler navbar-toggler-right" _type="button" />,
      ~props={"data-toggle": "collapse", "data-target": "#navbarResponsive", "aria-controls": "navbarResponsive",
              "aria-expanded": "false", "aria-label": "Toggle navigation"},
      [|<span className="navbar-toggler-icon"></span>|]
    );

  let navLinkDashboard = <a className="nav-link" href="#">
                          <i className="fa fa-fw fa-dashboard"></i>
                          <span className="nav-link-text">{ReasonReact.string("Dashboard")}</span>
                        </a>;

  let navLinkMenu = 
    ReasonReact.cloneElement(
      <a className="nav-link nav-link-collapse collapsed" href="#collapseMulti"/>,
      ~props={"data-toggle": "collapse", "data-parent": "#exampleAccordion"},
      [|<i className="fa fa-fw fa-sitemap"></i>, <span className="nav-link-text">{ReasonReact.string("Menu Levels")}</span>|]
    );

  let navItem = (title, child) =>
    ReasonReact.cloneElement(
      <li className="nav-item" title={title}/>,
      ~props={"data-toggle": "tooltip", "data-placement": "right"},
      [|child|]
    );  
  

  <nav className="navbar navbar-expand-lg navbar-dark bg-dark fixed-top" id="mainNav">
    <a className="navbar-brand" href="#">{ReasonReact.string("Logo")}</a>
    {togglerButton}
    <div className="collapse navbar-collapse" id="navbarResponsive">
      <ul className="navbar-nav navbar-sidenav" id="exampleAccordion">
        {navItem("Dashboard", navLinkDashboard)}
        {navItem("Menu Levels", navLinkMenu)}
      </ul>
      <ul className="navbar-nav sidenav-toggler">
        <li className="nav-item">
          <a className="nav-link text-center" id="sidenavToggler">
            <i className="fa fa-fw fa-angle-left"></i>
          </a>
        </li>
      </ul>
    </div>
  </nav>
  }
};