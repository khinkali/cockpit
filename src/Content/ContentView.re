let component = ReasonReact.statelessComponent("ContenCoverView");

let make = (_children) => {
  ...component,
  render: _self => {
    <div className="content-wrapper">
    <div className="container-fluid px-0">
      <ol className="breadcrumb py-3">
        <li className="breadcrumb-item font-weight-bold">
          <h3>{ReasonReact.stringToElement("Dashboard")}</h3> 
        </li>
      </ol>
      <div className="row">
        <footer className="sticky-footer">
          <div className="container">
            <div className="text-center">
              <small>{ReasonReact.stringToElement("Copyright © Your Website 2018")}</small>
            </div>
          </div>
        </footer>
        <a className="scroll-to-top rounded" href="#">
          <i className="fa fa-angle-up"></i>
        </a>
      </div>
    </div>
  </div>
  }
};