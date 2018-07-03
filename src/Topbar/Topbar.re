type state = {
  empty: int,
};

type action =
  | Nothing;


let component = ReasonReact.reducerComponent("Topbar");

let make = (_children) => {
  ...component,
  initialState: () => {empty: 0},
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: _self => {
    <header className="mdc-top-app-bar mdc-top-app-bar--fixed">
      <div className="mdc-top-app-bar__row">

        <section className="mdc-top-app-bar__section mdc-top-app-bar__section--align-start">
          <a href="#" className="mdc-top-app-bar__navigation-icon">
            <i className="fas fa-align-justify"></i>
          </a>
          <span className="mdc-top-app-bar__title">{ReasonReact.string("Title")}</span>
        </section>

        <section className="mdc-top-app-bar__section mdc-top-app-bar__section--align-end" role="toolbar">
          <a href="#" className="mdc-top-app-bar__action-item" ariaLabel="Bookmark this page" alt="Bookmark this page">
            <i className="fas fa-bookmark"></i>
          </a>
        </section>
        
      </div>
    </header>
  }
};

   