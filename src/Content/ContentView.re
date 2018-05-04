let component = ReasonReact.statelessComponent("ContenCoverView");

let make = (~coins: Coins.coins, _children) => {
  ...component,
  render: _self => {

    let createTd = (v: Coins.coin) =>
      <tr>
        <td>{ReasonReact.string(string_of_int(v.amount))}</td>
        <td>{ReasonReact.string(v.currency)}</td>
      </tr>;

    <div className="content-wrapper">
      <div className="container-fluid px-0">
        <ol className="breadcrumb py-3">
          <li className="breadcrumb-item font-weight-bold">
            <h3>{ReasonReact.string("Dashboard")}</h3> 
          </li>
        </ol>

        <div className="row ml-0">
          <table>
            <thead>
              <tr>
                <th>{ReasonReact.string("Month")}</th>
                <th>{ReasonReact.string("Savings")}</th>
              </tr>
            </thead>
            <tbody>
              {
                coins
                |> List.map(createTd)
                |> Array.of_list
                |> ReasonReact.array
              }
            </tbody>
          </table>
        </div> 
      </div>

      <footer className="sticky-footer">
        <div className="container">
          <div className="text-center">
            <small>{ReasonReact.string("Copyright 2018")}</small>
          </div>
        </div>
      </footer>
      <a className="scroll-to-top rounded" href="#">
        <i className="fa fa-angle-up"></i>
      </a> 
    </div>
  }
};