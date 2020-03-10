[@bs.val] external token: string = "process.env.GITHUB_TOKEN";
[@bs.val] external document: Js.t({..}) = "document";
[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";

open ReasonUrql;
open Hooks;

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= ExampleStyles.style;

[@react.component]
let make = _ => {
  let (stateVideos, setStateVideos) = React.useState(() => [||]);
  let (stateParcours, setStateParcours) = React.useState(() => [||]);

  let parcoursList = setter =>
    Js.Promise.(
      fetch("https:...")
      |> then_(response => response##json())
      |> then_(jsonResponse => {
           setStateParcours(jsonResponse);
           Js.Promise.resolve();
         })
      |> catch(_err => {
           setter(_previousState => []);
           Js.Promise.resolve();
         })
      |> ignore
    );

  let fetchOptions =
    Client.FetchOpts(
      Fetch.RequestInit.make(
        ~method_=Post,
        ~headers=
          Fetch.HeadersInit.make({
            "Content-Type": "application/json",
            "Authorization": "Bearer " ++ token,
          }),
        (),
      ),
    );

  // let message = Client.make(~url="", ~fetchOptions, ());

  // let parcoursList = Array.make(~url="localhost", ~fetchOptions, ());

  let welcome = <> <p> {React.string("BIENVENUE !")} </p> </>;

  let parcours = <> <div className="parentContainer" /> </>;
  //Récupérer les parcours ici

  let menuModules = <> </>;
  //Récupérer les modules ici

  let cours = <> </>;
  //Récupérer les cours ici

  <>
    <div className="bienvenue"> welcome </div>
    <div>
      {switch (stateParcours) {
       | [||] => React.string("Aucun parcour pour le moment")
       | default =>
         stateParcours
         ->Belt.Array.mapWithIndex((i, p) =>
             <div className="parcours"> p </div>
           )
         ->React.array
       }}
    </div>
    //      {stateParcours
    //       ->Belt.Array.mapWithIndex((i, p) =>
    //           <div className="parcours"> {React.string("BIENVENUE !")} </div>
    //         )
    //       ->React.array}
    <div className="parcours"> parcours </div>
    <div className="menuModules"> menuModules </div>
    <div className="cours"> cours </div>
  </>;
};