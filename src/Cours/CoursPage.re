[@bs.val] external token: string = "process.env.GITHUB_TOKEN";
[@bs.val] external document: Js.t({..}) = "document";

// We're using raw DOM manipulations here, to avoid making you read
// ReasonReact when you might precisely be trying to learn it for the first
// time through the examples later.
let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= CoursStyle.style;

open Cours;

[@react.component]
let make = (~title) => {

  let (stateCours, setStateCours) = React.useState(() => Cours.make("","",""));

  let decodeCours= json =>
    json |> Cours.fromJson
  ;

  let getModuleCours = (title) =>
    Js.Promise.(
      Fetch.fetchWithInit("",
      Fetch.RequestInit.make(~method_=Get, ()),)
      |> then_(Fetch.Response.json)
      |> then_(json  => {
           let decoded = decodeCours(json);
           setStateCours(_ => decoded);
           Js.Promise.resolve();
         })
//      |> catch(_err
//           // setter(_previousState => []);
//           => Js.Promise.resolve())
      |> ignore
    );

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
      <p> {React.string(title)} </p>
  </>;

  let description = 
  <>
  // Récupérer la description
  <p> {React.string(Cours.getDescription(stateCours))} </p>
  </>;

  let video = 
  <>
    //Récupérer la video
    <iframe  width="425" height="344" 
    src=Cours.getVideoUrl(stateCours) >
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