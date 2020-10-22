[@bs.module "yup-of-json"] external parse: string => string = "default";

[@react.component]
let make = () => {
  let (jsonSchema, setJsonSchema) =
    React.useState(() =>
      "{\n  \"addresses\": {\n    \"raw\": \"Kukuroo Mountain\"\n  },\n  \"age\": 14,\n  \"hunter\": true,\n  \"name\": \"Killua Zoldyck\",\n  \"role\": null,\n  \"tags\": [\n    {\n      \"label\": \"cute\"\n    }\n  ]\n}"
    );

  let (yupSchema, setYupSchema) = React.useState(() => "Killua <3");

  React.useEffect1(
    () => {
      let schema =
        try(parse(jsonSchema)) {
        | Js.Exn.Error(exn) =>
          switch (Js.Exn.message(exn)) {
          | Some(message) => message
          | None => "Unknown exception"
          }
        };

      setYupSchema(_ => schema);

      None;
    },
    [|jsonSchema|],
  );

  <>
    <div className="row">
      <textarea
        className="border-right textarea"
        onChange={event => {
          open ReactEvent.Form;

          persist(event);
          setJsonSchema(_ => target(event)##value);
        }}
        value=jsonSchema
      />
    </div>
    <div className="row">
      <textarea
        className="border-left textarea"
        readOnly=true
        value=yupSchema
      />
    </div>
  </>;
};
