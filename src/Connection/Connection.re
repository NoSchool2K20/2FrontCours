[@bs.val] external token: string = "process.env.GITHUB_TOKEN";
[@bs.val] external document: Js.t({..}) = "document";

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= ConnectionStyle.style;
[@react.component]
let make = _ => {

  let welcome =
  <>
  <p> {React.string("Connectez-vous !")} </p>
  </>;

  let formulaire =
  <>
      <AuthForm >
      </AuthForm>
  </>;

  <>
   // <div className="welcome"> welcome </div>
    <div className="FormulaireConnection"> formulaire </div>
  </>;
};