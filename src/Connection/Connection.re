[@bs.val] external token: string = "process.env.GITHUB_TOKEN";

[@react.component]
let make = _ => {

  let accueil =
  <>
      <p> {React.string("Connectez-vous")} </p>
  </>;

  let formulaire =
  <>
      // Récupérer le composant connection
  </>;

  <>
    <div className="accueilConnection"> accueil </div>
    <div className="FormulaireConnection"> formulaire </div>
  </>;
};