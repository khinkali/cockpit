module.exports = {
  "Add valid coin": function(client) {
    const user = client.globals.users.admin.user;
    const password = client.globals.users.admin.password;
    const auth = client.page.authentication();
    const newCoin = client.page.newCoin();
    //const link = client.page.link();
    const coinTable = client.page.coinTable();
    const menuNavi = client.page.menu();

    client.url(client.launchUrl);

    auth.login(user, password);
    client.pause(500);
    menuNavi.expect.section("@menu").to.be.visible;
    client.pause(500);

    newCoin.expect.section("@addNewCoin").to.be.visible;
    client.expect.element("#coin-overview").to.be.visible;

    coinTable.readValues(prevValues => {
      const addAmt = 400;
      const addCurr = "BTC";
      const prevCoin = prevValues.filter(c => c.currency === addCurr)[0];

      const addNewCoin = newCoin.section.addNewCoin;
      newCoin.addAmount(addAmt);
      newCoin.addCurrency(addCurr);
      addNewCoin.expect.element("@add").to.be.enabled;
      newCoin.addCoin();

      coinTable.readValues(afterValues => {
        const afterCoin = afterValues.filter(c => c.currency === addCurr)[0];
        client.assert.equal(parseInt(prevCoin.amount) + parseInt(addAmt), parseInt(afterCoin.amount));
        client.end();
      });
    });
  }
};
