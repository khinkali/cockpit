

type tab = {
  name: string,
  active: bool,
  icon: string,
};

type tabs = list(tab);

type state = {
  activeTab: tab
};

type action =
  | ClickedTab(tab);

let entryTab = {name: "Overview", active: true, icon: "fas fa-chart-area"};

let navTabs = [entryTab,
               {name: "Stocks", active: false, icon: "fas fa-balance-scale"}]; 

let component = ReasonReact.reducerComponent("SidebarContainer");

let make = (_children) => {
  ...component,
  initialState: () => entryTab,
  reducer: (_action: action, _state: state) => ReasonReact.NoUpdate,
  render: (_self) => {
    <div>
    </div>
  }
};