const commands = {
  addAmount: function(value) {
    return this.section.addNewCoin
      .waitForElementVisible("@amount", 3000)
      .setValue("@amount", value);
  },
  addCurrency: function(value) {
    return this.section.addNewCoin
      .waitForElementVisible("@currency", 3000)
      .click(`select[name=newcurrency] option[value='${value}']`);
  },
  addCoin: function() {
    return this.section.addNewCoin
      .waitForElementVisible("@add", 3000)
      .click("@add");
  }
};

module.exports = {
  commands: [commands],
  sections: {
    addNewCoin: {
      selector: "#add-new-coin",
      elements: {
        amount: {
          selector: "input[name=newamount]"
        },
        currency: {
          selector: "select[name=newcurrency]"
        },
        add: {
          selector: "button[name=addnewcoin]"
        }
      }
    }
  }
};
