module.exports = {

    "Add coin": function (browser) {

        const user = browser.globals.users.admin.user;
        const password = browser.globals.users.admin.password;


        browser
            .url(browser.launchUrl)
            .login(user, password)
            .waitForElementVisible("#linkAccount", 2000)
            .click("#linkAccount > a")
            .waitForElementVisible("#inputAmt", 2000)
            .setValue("#inputAmt", 33.333)
            .waitForElementVisible("#selectCurr", 2000)
            .click("select[id='selectCurr'] option[value='BTC']")
            .getAttribute("#btnAdd", "disable", (result) => {
                browser.expect.element('#btnAdd').to.be.enabled;
            })
            .end();

    }


}