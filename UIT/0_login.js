module.exports = {
    'Successfull Login': function (browser) {

        const user = browser.globals.users.admin.user;
        const password = browser.globals.users.admin.password;

        browser
            .url(browser.launchUrl)
            .login(user, password)
            .waitForElementVisible('#root > table > thead > tr > th:nth-of-type(2)', 2000)
            .assert.containsText('#root > table > thead > tr > th:nth-of-type(2)', 'Savings')
            .end();
    },
    'Failed Login': function (browser) {

        const user = browser.globals.users.wrongCredentials.user;
        const password = browser.globals.users.wrongCredentials.password;

        browser
            .url(browser.launchUrl)
            .login(user, password)
            .waitForElementVisible('.kc-feedback-text', 2000)
            .assert.containsText('.kc-feedback-text', 'Invalid username or password.')
            .end();
    }
};