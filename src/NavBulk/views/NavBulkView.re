

[%%raw {|import '../styles/navbulk.css'|}];
[%%raw {|import _logo from '../images/logo.svg'|}];

let logo = [%raw "_logo"];

let component = ReasonReact.statelessComponent("NavBulkView");

let setSectionRef = (theRef, _) => {
  let d: option(Dom.element) = Js.Nullable.toOption(theRef);
  switch d {
    | None => Js.log("Nothing")
    | Some(a) =>
      /*ElementRe.setClassName(a, "box");*/
      Js.log(ElementRe.innerText(a));
  };
};

let make = (_children) => {
  ...component,
  render: _self => {
    <nav className="navbar fixed-top navbar-light nav-bulk">
      <a className="navbar-brand" href="#">
        <img src={logo} width="30" height="30" alt=""/>
      </a>
    </nav>
  }
};