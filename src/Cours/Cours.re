[@bs.val] external token: string = "process.env.GITHUB_TOKEN";
[@bs.val] external document: Js.t({..}) = "document";

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= ExampleStyles.style;

[@react.component]
let make = _ => {

  let titre =
  <>
      // Récupérer le titre
      <p> {React.string("TITRE")} </p>
  </>;

  let description = 
  <>
  // Récupérer la description
  <p> {React.string("DESCRIPTION")} </p>
  </>;

  let video = 
  <>
    //Récupérer la video
    <p> {React.string("VIDEO")} </p>
  </>;

  let forum = 
  <>
    // Récupérer le forum
    <button
        onClick={_ => ReasonReactRouter.push("/")}>
        {React.string("Forum")}
      </button>
  </>;

  <>
    <div className="forumButton"> forum </div>
    <div className="titreCours"> titre </div>
    <div className="descriptionCours"> description </div>
    <div className="videoCours"> video </div>
  </>;
};