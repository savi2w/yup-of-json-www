const path = require("path");
const HtmlWebpackPlugin = require("html-webpack-plugin");

const output = path.join(__dirname, "build");

module.exports = {
  devServer: {
    contentBase: output,
    port: 3000,
  },
  entry: "./src/Index.bs.js",
  mode: process.env.NODE_ENV === "production" ? "production" : "development",
  module: {
    rules: [
      {
        test: /\.css$/,
        use: ["style-loader", "css-loader"],
      },
    ],
  },
  output: {
    filename: "Index.bs.js",
    path: output,
  },
  plugins: [
    new HtmlWebpackPlugin({
      favicon: "./public/favicon.ico",
      inject: false,
      template: "./public/index.html",
    }),
  ],
};
