[@bs.val] external token: string = "process.env.GITHUB_TOKEN";
[@bs.val] external document: Js.t({..}) = "document";
[@bs.val] external atob: string => Js.String.t = "atob";

// We're using raw DOM manipulations here, to avoid making you read
// ReasonReact when you might precisely be trying to learn it for the first
// time through the examples later.
let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= CoursStyle.style;

open Cours;
open User;

[@react.component]
let make = (~title) => {

  let (stateForum, setStateForum) = React.useState(() => false);
  let (stateCours, setStateCours) = React.useState(() => Cours.make("","",""));

  let decodeCours= json =>
    json |> Courslist.fromJson
  ;

  let getTok = () => {
let tok = Dom.Storage.getItem("token", Dom.Storage.localStorage);
  switch (tok) {
  | None => ""
  | Some(token) => token
  }
};
let body = getTok() |> Js.String.split(".") |> Js.Array.unsafe_get(_,1)
let jsonbody = try (Js.Json.parseExn(atob(body))) {
  | Not_found => Js.Json.null
  };

let decodeToken=json =>
  json |> User.fromJson

  let getModuleCours = (title) =>
    Js.Promise.(
      Fetch.fetchWithInit("http://18.220.58.155:8080/cours/?title=" ++ title,
      Fetch.RequestInit.make(~method_=Get,
        ~headers=Fetch.HeadersInit.make({"Authorization": "Bearer " ++ getTok()}),()),)
      |> then_(Fetch.Response.json)
      |> then_(json  => {
           let decoded = decodeCours(json);
           setStateCours(_ => List.nth(decoded,0));
           Js.Promise.resolve();
         })
      |> catch(_err
           => Js.Promise.resolve())
      |> ignore
    );

  React.useEffect0(() => {
    getModuleCours(title);
    None;
  });

  let accueil = 
  <>
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
        onClick={_ => setStateForum(_ => true);}>
        {React.string("Forum")}
      </button>
  </>;

let getTok = () => {
let tok = Dom.Storage.getItem("token", Dom.Storage.localStorage);
  switch (tok) {
  | None => ""
  | Some(token) => token
  }
};


  let forum =
  <>
        <Forum token=User.getName(decodeToken(jsonbody)) titleCours=title >
        </Forum>
  </>;

  <>
    <div className="accueilButton"> accueil </div>
    <div className="forumButton"> buttonForum </div>
    <div className="titreCours"> titre </div>
    <div className="descriptionCours"> description </div>
    <div className="videoCours">video</div>
     
     {switch (stateForum) {
           | true =>
             forum
           | _ =>
            <p> </p>
           }}
  </>;
};