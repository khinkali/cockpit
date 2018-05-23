module.exports = {
    '[61] Login': function (browser) {

        const user = browser.globals.users.agateBenutzer.user;
        const password = browser.globals.users.agateBenutzer.password;

        browser
            .url(browser.launchUrl)
            .waitForElementVisible('#isiwebuserid', 5000)
            .setValue('#isiwebuserid', user)
            .waitForElementVisible('#isiwebpasswd', 5000)
            .setValue('#isiwebpasswd', password)
            .waitForElementVisible('#first', 5000)
            .click('#first')
            .pause(1000)
            .acceptAlert()
            .waitForElementVisible('#root', 10000)
            .pause(500)
            .assert.containsText('#root', 'Meine Zugänge')
            .end();
    },

    '[61] Login Failure with wrong credentials': function (browser) {

        const user = 'WrongUsername';
        const password = 'unexistingPassword';

        browser
            .url(browser.launchUrl)
            .waitForElementVisible('#isiwebuserid', 5000)
            .setValue('#isiwebuserid', user)
            .waitForElementVisible('#isiwebpasswd', 5000)
            .setValue('#isiwebpasswd', password)
            .waitForElementVisible('#first', 5000)
            .click('#first')
            .waitForElementVisible('.alert-danger', 5000)
            .assert.containsText('.alert-danger', 'Ihr Login ist fehlgeschlagen. Bitte überprüfen Sie Ihre Eingabe.')
            .end();
    }
};