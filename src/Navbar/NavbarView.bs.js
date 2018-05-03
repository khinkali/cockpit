// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE

import * as React from "react";
import * as ReasonReact from "reason-react/src/ReasonReact.js";

var component = ReasonReact.statelessComponent("NavbarView");

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
              var togglerButton = React.cloneElement(React.createElement("button", {
                        className: "navbar-toggler navbar-toggler-right",
                        type: "button"
                      }), {
                    "data-toggle": "collapse",
                    "data-target": "#navbarResponsive",
                    "aria-controls": "navbarResponsive",
                    "aria-expanded": "false",
                    "aria-label": "Toggle navigation"
                  }, React.createElement("span", {
                        className: "navbar-toggler-icon"
                      }));
              var navLinkDashboard = React.createElement("a", {
                    className: "nav-link",
                    href: "#"
                  }, React.createElement("i", {
                        className: "fa fa-fw fa-dashboard"
                      }), React.createElement("span", {
                        className: "nav-link-text"
                      }, "Dashboard"));
              var navLinkMenu = React.cloneElement(React.createElement("a", {
                        className: "nav-link nav-link-collapse collapsed",
                        href: "#collapseMulti"
                      }), {
                    "data-toggle": "collapse",
                    "data-parent": "#exampleAccordion"
                  }, React.createElement("i", {
                        className: "fa fa-fw fa-sitemap"
                      }), React.createElement("span", {
                        className: "nav-link-text"
                      }, "Menu Levels"));
              var navItem = function (title, child) {
                return React.cloneElement(React.createElement("li", {
                                className: "nav-item",
                                title: title
                              }), {
                            "data-toggle": "tooltip",
                            "data-placement": "right"
                          }, child);
              };
              return React.createElement("nav", {
                          className: "navbar navbar-expand-lg navbar-dark bg-dark fixed-top",
                          id: "mainNav"
                        }, React.createElement("a", {
                              className: "navbar-brand",
                              href: "#"
                            }, "Logo"), togglerButton, React.createElement("div", {
                              className: "collapse navbar-collapse",
                              id: "navbarResponsive"
                            }, React.createElement("ul", {
                                  className: "navbar-nav navbar-sidenav",
                                  id: "exampleAccordion"
                                }, navItem("Dashboard", navLinkDashboard), navItem("Menu Levels", navLinkMenu)), React.createElement("ul", {
                                  className: "navbar-nav sidenav-toggler"
                                }, React.createElement("li", {
                                      className: "nav-item"
                                    }, React.createElement("a", {
                                          className: "nav-link text-center",
                                          id: "sidenavToggler"
                                        }, React.createElement("i", {
                                              className: "fa fa-fw fa-angle-left"
                                            }))))));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

export {
  component ,
  make ,
  
}
/* component Not a pure module */
