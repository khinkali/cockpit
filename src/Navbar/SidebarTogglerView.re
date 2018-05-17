open Webapi.Dom;

let component = ReasonReact.statelessComponent("SidebarTogglerView");

let handleClick = (_event, _self) => {
  switch (Document.getElementById("doc-page", document)) {
  | Some(ele) => 
      DomTokenListRe.toggle("sidenav-toggled", Element.classList(ele))
      |> ignore;
  | None => ();
  }; 
};

let make = (_children) => {
  ...component,
  render: self => {
    <ul className="navbar-nav sidenav-toggler">
      <li className="nav-item">
        <a className="nav-link text-center" id="sidenavToggler" onClick={self.handle(handleClick)}>
          <i className="fa fa-fw fa-angle-left"></i>
        </a>
      </li>
    </ul>
  }
};