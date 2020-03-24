[@bs.val] external token: string = "process.env.GITHUB_TOKEN";
[@bs.val] external document: Js.t({..}) = "document";

// We're using raw DOM manipulations here, to avoid making you read
// ReasonReact when you might precisely be trying to learn it for the first
// time through the examples later.
let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= CoursStyle.style;

[@react.component]
let make = _ => {


  let accueil = 
  <>
    // Récupérer le forum
    <button
        onClick={_ => ReasonReactRouter.push("/")}>
        {React.string("Accueil")}
      </button>
  </>;

  let titre =
  <>
      // Récupérer le titre
      <p> {React.string("TITRE DU COURS NUMERO 1")} </p>
  </>;

  let description = 
  <>
  // Récupérer la description
  <p> {React.string("Le but de ce cours est de pouvoir tester le CSS de NotOnlyASchool.")} </p>
  </>;

  let video = 
  <>
    //Récupérer la video
    <iframe  width="425" height="344" 
    src="http://www.youtube.com/embed/_-KEFeWLVtY" >
    </iframe>
  </>;

  let buttonForum =
  <>
    // Récupérer le forum
    <button
        onClick={_ => ReasonReactRouter.push("/")}>
        {React.string("Forum")}
      </button>
  </>;

  let forum =
  <>
        <Forum name="Imani">
          <div> {React.string("Effectively the child.")} </div>
        </Forum>
  </>;

  <>
    <div className="accueilButton"> accueil </div>
    <div className="forumButton"> buttonForum </div>
    <div className="titreCours"> titre </div>
    <div className="descriptionCours"> description </div>
    <div className="videoCours">video</div>
  </>;
};