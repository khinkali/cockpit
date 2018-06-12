module.exports = {
    'Successfull Login': function (browser) {

        const user = browser.globals.users.admin.user;
        const password = browser.globals.users.admin.password;

        browser
            .url(browser.launchUrl)
            .login(user, password)
            .waitForElementVisible('.mdc-drawer__header-content', 2000)
            .assert.containsText('.mdc-drawer__header-content', 'Header')
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