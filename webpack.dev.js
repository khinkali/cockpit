const merge = require("webpack-merge");
const common = require("./webpack.common.js");
const webpack = require("webpack");
const path = require("path");

module.exports = merge(common, {
  mode: "development",
  devServer: {
    contentBase: path.resolve(__dirname, "public"),
    compress: false,
    port: 9000,
    hot: true
  },
  plugins: [new webpack.HotModuleReplacementPlugin({})]
});
