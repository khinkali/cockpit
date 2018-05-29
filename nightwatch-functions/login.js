exports.command = function (username, password) {

    this
        .waitForElementVisible('#username', 2000)
        .setValue('#username', username)
        .waitForElementVisible('#password', 2000)
        .setValue('#password', password)
        .waitForElementVisible('#kc-login', 2000)
        .click('#kc-login');

    return this;
};