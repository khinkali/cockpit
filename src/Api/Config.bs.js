// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE

import * as Axios from "axios";

var read = Axios.get("config.json").then((function (x) {
          return Promise.resolve(x.data.env.url);
        })).then((function (x) {
        return Promise.resolve(x);
      }));

export {
  read ,
  
}
/* read Not a pure module */
