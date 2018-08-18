type state = {
  showMobileMenu: bool,
  mobileMenuAnimate: string,
};

type action =
  | MobileMenuToggler(bool);

let component = ReasonReact.reducerComponent("Topbar");

let toggleMobileMenu = (toggler: bool) =>
  toggler ? "topbar-animate-forward" : "topbar-animate-backward";

let make = (~onClick: 'a => unit, _children) => {
  ...component,
  initialState: () => {showMobileMenu: false, mobileMenuAnimate: ""},
  reducer: (action: action, state: state) =>
    switch (action) {
    | MobileMenuToggler(t) =>
      let toggler = !t;
      ReasonReact.Update({
        showMobileMenu: toggler,
        mobileMenuAnimate: toggleMobileMenu(toggler),
      });
    },
  render: self =>
    <div className="topbar-container">
      <section className="topbar-menu">
        <a
          onClick={
            _evt => self.send(MobileMenuToggler(self.state.showMobileMenu))
          }
          className="topbar-navi-menu">
          <i className={self.state.mobileMenuAnimate} />
          <i className={self.state.mobileMenuAnimate} />
          <i className={self.state.mobileMenuAnimate} />
        </a>
      </section>
    </div>,
};