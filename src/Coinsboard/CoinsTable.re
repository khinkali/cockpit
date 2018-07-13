let component = ReasonReact.statelessComponent("CoinsTable");

let make = (~coins: Coins.coins, _children) => {
  ...component,
  render: _self => {
    <table className="table">
      <thead>
        <tr>
          <th>{ReasonReact.string("Amount")}</th>
          <th>{ReasonReact.string("Currency")}</th>
        </tr>
      </thead>
      <tbody></tbody>
    </table>
  }
};