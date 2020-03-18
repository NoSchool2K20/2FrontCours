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

  let welcome = <> <p> {React.string("BIENVENUE !")} </p> 
  <p> {React.string("Choisissez votre parcours : ")} </p></>;

  let parcours = //<> <div className="parentContainer" /> </>;
  <>
  <button
    onClick={_ => ReasonReactRouter.push("/")}>
    {React.string("Cyberdefense")}
  </button>
  <button
    onClick={_ => ReasonReactRouter.push("/")}>
    {React.string("Developpement web")}
  </button>
  </>

  //Récupérer les modules ici
  let make = children =>
    ReasonReact.wrapJsForReason(
      ~reactClass=myJSReactClass,
      ~props=jsProps(~className="module", ~modules=stateModules),
      children,
    );
  let menuModules = <> 
  <button
              onClick={_ => ReasonReactRouter.push("/")}>
              {React.string("Module 1")}
          </button>
          <button
              onClick={_ => ReasonReactRouter.push("/")}>
              {React.string("Module 2")}
          </button>
          <button
              onClick={_ => ReasonReactRouter.push("/")}>
              {React.string("Module 3")}
          </button>
          <button
              onClick={_ => ReasonReactRouter.push("/")}>
              {React.string("Module 4")}
          </button>
  </>;

  let cours = 
  <> 
  <div>
        <p className="titre"> {React.string("Cours 1")} </p> 
        <p> {React.string("Description cours 1")} </p>
        <button
              onClick={_ => ReasonReactRouter.push("/")}>
              {React.string("Acces au contenu")}
          </button>
      </div>

    <div>
        <p className="titre"> {React.string("Cours 2")} </p> 
        <p> {React.string("Description cours 2")} </p>
        <button
              onClick={_ => ReasonReactRouter.push("/")}>
              {React.string("Acces au contenu")}
          </button>
      </div>
      <div>
        <p className="titre"> {React.string("Cours 3")} </p> 
        <p> {React.string("Description cours 3")} </p>
        <button
              onClick={_ => ReasonReactRouter.push("/")}>
              {React.string("Acces au contenu")}
          </button>
      </div>
  </>;
  //Récupérer les cours ici

  <>
    <div className="bienvenue"> welcome </div>
    <div>
      {switch (stateParcours) {
       | [||] =>
         <div className="parcours"> parcours
           
         </div>
       | default =>
         stateParcours
         ->Belt.Array.mapWithIndex((i, p) =>
             <div className="parcours"> p </div>
           )
         ->React.array
       }}
    </div>

    <div className="menuModules"> 
    menuModules
    </div>

    <div className="cours"> 
    cours 
    </div>
  </>;
};
