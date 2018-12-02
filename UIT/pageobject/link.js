const commands = {
  navigate: function(name) {
    return this.section.navBar
      .click(`a[href='/${name}']`);
  }
};

module.exports = {
  commands: [commands],
  sections: {
    navBar: {
      selector: "#navigation"
    }
  }
};
