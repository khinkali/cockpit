module.exports = {
    'Successfull Login': function (browser) {

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
    },
    'Failed Login': function (browser) {

        const user = browser.globals.users.wrongCredentials.user;
        const password = browser.globals.users.wrongCredentials.password;

        browser
            .url(browser.launchUrl)
            .waitForElementVisible('#username', 5000)
            .setValue('#username', user)
            .waitForElementVisible('#password', 5000)
            .setValue('#password', password)
            .waitForElementVisible('#kc-login', 5000)
            .click('#kc-login')
            .pause(1000)
            .waitForElementVisible('.kc-feedback-text', 10000)
            .pause(500)
            .assert.containsText('.kc-feedback-text', 'Invalid username or password.')
            .end();
    }
};