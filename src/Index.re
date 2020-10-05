[@bs.module "normalize.css"] external normalize: string = "normalize";
normalize;

[%bs.raw {|require("./public/styles.css")|}];

ReactDOMRe.renderToElementWithClassName(<App />, "root");
