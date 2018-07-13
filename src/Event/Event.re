  let valueFromKeyUp = evt => ReactDOMRe.domElementToObj(
                                              ReactEventRe.Keyboard.target(
                                                evt,
                                              ),
                                            )##value;                                          

  let valueFromForm = evt => ReactDOMRe.domElementToObj(
                                             ReactEventRe.Form.target(evt),
                                           )##value;