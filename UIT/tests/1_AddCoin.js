module.exports = {
  "Add coin": function(client) {
    const user = client.globals.users.admin.user;
    const password = client.globals.users.admin.password;
    const kc = client.page.login();

    client.url(client.launchUrl);
    kc.login(user, password);

    client
      .click("a[href='/account']")
      .waitForElementVisible("input[name=newamount]", 2000)
      .setValue("input[name=newamount]", 33.33)
      .waitForElementVisible("select[name=newcurrency]", 2000)
      .click("select[name=newcurrency] option[value='ETH']");

    client.expect.element("button[name=addnewcoin]").to.be.enabled;

    client.expect.element("#coins-view").
    
    client.end();

  }
};
