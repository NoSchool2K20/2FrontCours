[@bs.val] external token: string = "process.env.GITHUB_TOKEN";
[@bs.val] external document: Js.t({..}) = "document";

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= ExampleStyles.style;

[@react.component]
let make = _ => {

  let welcome =
  <>
      <p>{React.string("BIENVENUE !")}</p>
  </>;

  let parcours = 
  <>
  //Récupérer les parcours ici
  </>;

  let menuModules = 
  <>
    //Récupérer les modules ici
  </>;

  let cours = 
  <>
    //Récupérer les cours ici
  </>;

  <>
    <div className="bienvenue"> welcome </div>
    <div className="parcours"> parcours </div>
    <div className="menuModules"> menuModules </div>
    <div className="cours"> cours </div>
  </>;
};