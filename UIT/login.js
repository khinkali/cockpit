module.exports = {
    '[61] Login': function (browser) {

        const user = browser.globals.users.admin.user;
        const password = browser.globals.users.admin.password;

        browser
            .url(browser.launchUrl)
            .waitForElementVisible('#username', 5000)
            .setValue('#username', user)
            .waitForElementVisible('#password', 5000)
            .setValue('#password', password)
            .waitForElementVisible('#kc-login', 5000)
            .click('#kc-login')
            .pause(1000)
            .waitForElementVisible('#root', 10000)
            .pause(500)
            .assert.containsText('#root', 'Savings')
            .end();
    }
};