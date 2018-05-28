const merge = require("webpack-merge");
const common = require("./webpack.common.js");
const webpack = require("webpack");
const path = require("path");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");

module.exports = merge(common, {
  mode: "development",
  devServer: {
    contentBase: path.resolve(__dirname, "public"),
    compress: true,
    port: 9000,
    hot: true
  },
  plugins: [
    new webpack.HotModuleReplacementPlugin({}),
    new MiniCssExtractPlugin({
      filename: "[name].css",
      chunkFilename: "[id].css"
    })
  ]
});
