let component = ReasonReact.statelessComponent("CoinsList");

let make =
    (
      ~coins: Coins.coins,
      _children,
    ) => {
  ...component,
  render: _self => {
    let createTd = (idx, v: Coins.coin) =>
      <tr key=("Ci" ++ string_of_int(idx))>
        <td> (ReasonReact.string(string_of_int(v.amount))) </td>
        <td> (ReasonReact.string(v.currency)) </td>
      </tr>;

    <Fragment>
      <table id="coin-table">
        <thead>
          <tr>
            <th> (ReasonReact.string("Month")) </th>
            <th> (ReasonReact.string("Savings")) </th>
          </tr>
        </thead>
        <tbody>
          (
            coins
            |. Belt.List.mapWithIndex(createTd)
            |> Array.of_list
            |> ReasonReact.array
          )
        </tbody>
      </table>
    </Fragment>;
  },
};