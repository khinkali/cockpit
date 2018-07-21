let component = ReasonReact.statelessComponent("CoinsTable");

let make = (~coins: Coins.coins, _children) => {
  ...component,
  render: _self => {
    let row = (i: int, c: Coins.coin) => {
      <tr key=("coin-table-" ++ (i |> string_of_int))>
        <td> (c.amount |> string_of_float |> ReasonReact.string) </td>
        <td> (c.currency |> ReasonReact.string) </td>
      </tr>;
    };

    <table>
      <thead>
        <tr>
          <th> (ReasonReact.string("Amount")) </th>
          <th> (ReasonReact.string("Currency")) </th>
        </tr>
      </thead>
      <tbody>
        (coins |. Belt.Array.mapWithIndex(row) |> ReasonReact.array)
      </tbody>
    </table>;
  },
};