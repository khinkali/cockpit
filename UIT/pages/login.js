const commands = {
  login: function(username, password) {
    return this.waitForElementVisible("@usernameInput", 2000)
      .setValue("@usernameInput", username)
      .waitForElementVisible("@passwordInput", 2000)
      .setValue("@passwordInput", password)
      .waitForElementVisible("@loginInput", 2000)
      .click("@loginInput");
  }
};

module.exports = {
  commands: [commands],
  elements: {
    usernameInput: {
      selector: "input[name=username]"
    },
    passwordInput: {
      selector: "input[name=password]"
    },
    loginInput: {
      selector: "input[name=login]"
    }
  }
};
