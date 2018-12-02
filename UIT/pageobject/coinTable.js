const tableId = "#coins-table";

const commands = {
  readValues: function(cb) {
    return this.section.overview
      .waitForElementVisible("@table", 3000)
      .api.perform(done => {
        let values = [];

        this.api.elements("css selector", tableId + " > tbody > tr", trs => {
          trs.value.forEach(ele => {
            this.api.elementIdText(ele.ELEMENT, tr => {
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
  }
};

module.exports = {
  commands: [commands],
  sections: {
    overview: {
      selector: "#coin-overview",
      elements: {
        table: tableId
      }
    }
  }
};
