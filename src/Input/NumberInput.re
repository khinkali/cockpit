type state = {value: string};

type action =
  | OnKeyUp(int, string);

let allowedKeyCode = [48, 49, 50, 51, 52, 53, 54, 55, 56, 57];

let component = ReasonReact.reducerComponent("NumberInput");

let make = (~name: string, ~value: string => unit, ~maxLength: int, _children) => {
  ...component,
  initialState: () => {value: ""},
  reducer: (action, state: state) =>
    switch (action) {
    | OnKeyUp(keyCode, key) =>
      List.mem(keyCode, allowedKeyCode) ?
        ReasonReact.UpdateWithSideEffects(
          {value: state.value ++ key},
          (self => value(self.state.value)),
        ) :
        ReasonReact.NoUpdate
    },
  render: self =>
    <input
      type_="text"
      maxLength
      name
      value=self.state.value
      onKeyUp=(
        event =>
          self.send(
            OnKeyUp(
              ReactEventRe.Keyboard.keyCode(event),
              ReactEventRe.Keyboard.key(event),
            ),
          )
      )
    />,
};