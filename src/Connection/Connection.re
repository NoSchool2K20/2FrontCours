[@bs.val] external token: string = "process.env.GITHUB_TOKEN";

[@react.component]
let make = _ => {

  let accueil =
  <>
      <p> {React.string("Connectez-vous")} </p>
  </>;

  let formulaire =
  <>
      <Form name="Imani">
        <div> {React.string("Effectively the child.")} </div>
      </Form>
  </>;

  <>
    <div className="accueilConnection"> accueil </div>
    <div className="FormulaireConnection"> formulaire </div>
  </>;
};