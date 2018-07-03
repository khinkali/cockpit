type state = {empty: int};

type action =
  | None;


let component = ReasonReact.reducerComponent("SidebarContainer");

let make = _children => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: _self =>
    <nav className="mdc-drawer mdc-drawer--permanent ">
      <div className="mdc-list-group">
        <nav className="mdc-list">
          <a className="mdc-list-item" href="#">
            <i className="fas fa-inbox fa-lg mdc-list-item__graphic" />
            (ReasonReact.string("Star"))
          </a>
          <a className="mdc-list-item" href="#">
            <i
              className="fas fa-share-square fa-lg mdc-list-item__graphic"/>
            (ReasonReact.string("Sent Mail"))
          </a>
        </nav>
      </div>
    </nav>,
};