[@bs.val] external token: string = "process.env.GITHUB_TOKEN";
[@bs.val] external document: Js.t({..}) = "document";

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= ExampleStyles.style;

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