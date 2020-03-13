[@bs.val] external token: string = "process.env.GITHUB_TOKEN";
[@bs.val] external document: Js.t({..}) = "document";
[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";
[@bs.module "./TabsModule"]
external myJSReactClass: ReasonReact.reactClass = "TabsModule";

open ReasonUrql;
open Hooks;

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= HomeStyle.style;

[@bs.deriving jsConverter]
type moduleParcours = {title: string};

[@bs.deriving abstract]
type jsProps = {
  /* some example fields */
  className: string,
  modules: array(moduleParcours),
  //    /* `type` is reserved in Reason. use `type_` and make it still compile to the
  //       JS key `type` */
  //    [@bs.as "type"]
  //    type_: string,
  //    value: Js.nullable(int),
};

[@react.component]
let make = _ => {
  let (stateVideos, setStateVideos) = React.useState(() => [||]);
  let (stateParcours, setStateParcours) = React.useState(() => [||]);
  let (stateModules, setStateModules) = React.useState(() => [||]);

  // Requests API
  let parcoursList = () =>
    Js.Promise.(
      fetch("http://localhost:8080/pokemon-types/")
      |> then_(response => response##json())
      |> then_(jsonResponse => {
           setStateParcours(jsonResponse);
           Js.Promise.resolve();
         })
      |> catch(_err
           // setter(_previousState => []);
           => Js.Promise.resolve())
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
  React.useEffect0(() => {
    parcoursList();
    None;
  });

  // Render //

  let welcome = <> <p> {React.string("BIENVENUE !")} </p> </>;

  let parcours = <> <div className="parentContainer" /> </>;
  //Récupérer les parcours ici

  //Récupérer les modules ici
  let make = children =>
    ReasonReact.wrapJsForReason(
      ~reactClass=myJSReactClass,
      ~props=jsProps(~className="module", ~modules=stateModules),
      children,
    );
  let menuModules = <> </>;

  let cours = <> </>;
  //Récupérer les cours ici

  <>
    <div className="bienvenue"> welcome </div>
    <div>
      {switch (stateParcours) {
       | [||] =>
         <div className="parcours">
           {React.string("Aucun parcours pour le moment")}
         </div>
       | default =>
         stateParcours
         ->Belt.Array.mapWithIndex((i, p) =>
             <div className="parcours"> p </div>
           )
         ->React.array
       }}
    </div>
    <div className="menuModules"> menuModules </div>
    //    <div className="cours"> cours </div>
  </>;
};