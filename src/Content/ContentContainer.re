%raw "import './scss/content.scss'";

type state = {
  empty: int,
};

type action =
  | Nothing;


let component = ReasonReact.reducerComponent("ContentContainer");

let make = (children) => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: _self => {
    ReasonReact.createDomElement("div", ~props={"className": "content"}, children);
  }
};