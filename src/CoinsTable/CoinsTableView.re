let component = ReasonReact.statelessComponent("CoinsTableView");

let make =
    (
      ~coins: Coins.coins,
      ~amountEvent: string => unit,
      ~currEvent: string => unit,
      ~submitCoin: unit => unit,
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
      <table>
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
      <form onSubmit=(_event => submitCoin())>
        <label>
          (ReasonReact.string("Amount :"))
          <input
            type_="text"
            onChange=(
              event =>
                currEvent(
                  ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value,
                )
            )
          />
        </label>
        <label>
          (ReasonReact.string("Currency :"))
          <input
            type_="text"
            onChange=(
              event =>
                amountEvent(
                  ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value,
                )
            )
          />
        </label>
        <input type_="submit" value="Add coins" />
      </form>
    </Fragment>;
  },
};