// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE

import * as React from "react";
import * as ReasonReact from "reason-react/src/ReasonReact.js";
import * as NavbarView$Cockpit from "../Navbar/NavbarView.bs.js";
import * as ContentContainer$Cockpit from "../Content/ContentContainer.bs.js";

var component = ReasonReact.reducerComponent("AppContainer");

function make() {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function () {
              return React.createElement("div", undefined, ReasonReact.element(/* None */0, /* None */0, NavbarView$Cockpit.make(/* array */[])), ReasonReact.element(/* None */0, /* None */0, ContentContainer$Cockpit.make(/* array */[])));
            }),
          /* initialState */(function () {
              return /* record */[/* empty */0];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (_, _$1) {
              return /* NoUpdate */0;
            }),
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

var $$default = ReasonReact.wrapReasonForJs(component, (function () {
        return make(/* array */[]);
      }));

export {
  component ,
  make ,
  $$default ,
  $$default as default,
  
}
/* component Not a pure module */
