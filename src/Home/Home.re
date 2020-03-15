[@bs.val] external token: string = "process.env.GITHUB_TOKEN";

[@react.component]
let make = _ => {

  let welcome =
  <>
      <p>{React.string("BIENVENUE !")}</p>
  </>;

  let parcours = 
  <>
  </>;

  let menuModules = 
  <>
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