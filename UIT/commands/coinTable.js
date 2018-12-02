exports.command = function(tabelId, cb) {
  return this.waitForElementVisible(tabelId, 3000).perform(done => {
    let values = [];

    this.elements("css selector", tabelId + " > tbody > tr", trs => {
      trs.value.forEach((ele) => {
        this.elementIdText(ele.ELEMENT, tr => {
          const [amount, currency] = tr.value.split(" ");
          const coin = { amount: amount, currency: currency };
          values.push(coin);
          if (values.length === trs.value.length) {
            cb(values);
            done();
          }
        });
      });
    });
  });
};
