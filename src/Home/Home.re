[@bs.val] external token: string = "process.env.GITHUB_TOKEN";
[@bs.val] external document: Js.t({..}) = "document";
[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";
[@bs.val] external atob: string => string = "atob";
[@bs.val] external btoa: string => string = "btoa";
[@bs.module "js-base64"] external decode: string => string = "decode";

open Parcours;
open Parcourslist;
open Module;
open Moduleslist;
open Cours;

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= HomeStyle.style;

//[@bs.deriving jsConverter]
//type modules = {title: string};

[@bs.deriving abstract]
type jsProps = {

  className: string,
  modules: Moduleslist.t,
  parcours: Parcourslist.t,
  cours: Courslist.t,

  //    /* `type` is reserved in Reason. use `type_` and make it still compile to the
  //       JS key `type` */
  //    [@bs.as "type"]
  //    type_: string,
  //    value: Js.nullable(int),
};

[@react.component]
let make = _ => {
let (stateParcours, setStateParcours) = React.useState(() => []);
let (stateModules, setStateModules) = React.useState(() => []);
let (stateCours, setStateCours) = React.useState(() => []);
  

  let decodeParcours= json =>
    json |> Parcourslist.fromJson
  ;

  let decodeModules= json =>
    json |> Moduleslist.fromJson
  ;

  let decodeCours= json =>
    json |> Courslist.fromJson
  ;

  let getModuleCours = (title) =>
    Js.Promise.(
      Fetch.fetchWithInit("http://18.220.58.155:8080/cours/?module=" ++ title,
      Fetch.RequestInit.make(~method_=Get, ()),)
      |> then_(Fetch.Response.json)
      |> then_(json  => {
           let decoded = decodeCours(json);
           setStateCours(_ => List.append([], decoded));
           Js.Promise.resolve();
         })

      |> catch(_err
           => Js.Promise.resolve())
      |> ignore
    );

  let getParcoursModules = (title) =>
    Js.Promise.(
      Fetch.fetchWithInit("http://18.220.58.155:8080/module/?parcours=" ++ title,
      Fetch.RequestInit.make(~method_=Get, ()),)
      |> then_(Fetch.Response.json)
      |> then_(json  => {
           let decoded = decodeModules(json);
           setStateModules(_ => List.append([], decoded));
           getModuleCours(Modules.getTitle(List.nth(decoded,0)));
           Js.Promise.resolve();

         })
      |> catch(_err
           => Js.Promise.resolve())
      |> ignore
    );

  // Requests API
  let parcoursList = () =>
    Js.Promise.(
      Fetch.fetchWithInit("http://18.220.58.155:8080/parcours",
      Fetch.RequestInit.make(~method_=Get, ()),)
      |> then_(Fetch.Response.json)
      |> then_(json  => {
           let decoded = decodeParcours(json);
           setStateParcours(_ => List.append(stateParcours, decoded));
           getParcoursModules(Parcours.getTitle(List.nth(decoded,0)));
           Js.Promise.resolve();

         })
      |> catch(_err
           => Js.Promise.resolve())
      |> ignore
    );

  React.useEffect0(() => {
    parcoursList();
    None;
  });

  // Render //

let getTok = () => {
let tok = Dom.Storage.getItem("token", Dom.Storage.localStorage);
  switch (tok) {
  | None => ""
  | Some(token) => token
  }
};

let deco = () => {
  let ls = Dom.Storage.localStorage;
  Dom.Storage.setItem("token","", ls); 
  ReasonReactRouter.push("/connection")
  Js.log(Dom.Storage.getItem("token"));
}
//Js.log(JsonWebToken.(getTok()));
let welcome=
<>
  <p>
    //{React.string(getTok() |> decode)}
  </p>
</>;

  let buttonDroits=
  <>
  <button
    onClick={_ => ReasonReactRouter.push("/upgrade")}>
    {React.string("Elevation de privileges")}
  </button>
  </>;

  let buttonDeconnection=
  <>
  <button
    onClick={_ => deco()}>
    {React.string("Deconnection")}
  </button>
  </>;

  let buttonAjoutCours=
  <>
  <button
    onClick={_ => ReasonReactRouter.push("/addCours")}>
    {React.string("Ajouter un cours")}
  </button>
  </>;

  //Récupérer les modules ici
  /*let make = children =>
    ReasonReact.wrapJsForReason(
      ~reactClass=myJSReactClass,
      ~props=jsProps(~className="module", ~modules=stateModules),
      children,
    );*/

  <>
    <div className="buttonDeconnection"> buttonDeconnection </div>
    <div className="buttonPrivileges"> buttonDroits </div>
    <div className="bienvenue"> welcome </div>
    <div>
      {switch (stateParcours) {
       | [] =>
         <div className="parcours"> 
           {React.string("Aucun parcours pour le moment")}
         </div>
       | _ =>
        <div className="parcoursList">
        <div className="choseParcours">  {React.string("Nos parcours")} </div>
              (
                React.array(Array.of_list(
                    List.map((p) =>
                    <div className="parcours" onClick={(_) => {getParcoursModules(Parcours.getTitle(p));();}}> {React.string(Parcours.getTitle(p))} </div>
                    , stateParcours)
                ))
              )
        </div>
       }}
    </div>

    <div className="menuModules"> 
    {switch (stateModules) {
           | [] =>
             <button>
                {React.string("Aucun Module")}
             </button>
           | _ =>
            (
                React.array(Array.of_list(
                    List.map((m) =>
                        <button name="boutonModule"
                            onClick={(_) => {getModuleCours(Modules.getTitle(m));();}}>
                            {React.string(Modules.getTitle(m))}
                        </button>
                        , stateModules)
                 ))
            )
           }}
    </div>

    <div className="cours">
    <div className="buttonAjoutCours"> buttonAjoutCours </div>

    {switch (stateCours) {
               | [] =>
                 <div className="leCours">
    
                    <p> {React.string("Aucun cours pour le moment")} </p>
                  </div>
               | _ =>
                (
                    React.array(Array.of_list(
                        List.map((c) =>
                            <div className="leCours">
                                <p className="titre"> {React.string(Cours.getTitle(c))} </p>
                                <p> {React.string(Cours.getDescription(c))} </p>
                                <button
                                    onClick={ _=> ReasonReactRouter.push("/cours/" ++ Cours.getTitle(c))}>
                                    {React.string("Acces au contenu")}
                                </button>
                            </div>
                            , stateCours)
                     ))
                )
    }}
    </div>
  </>;
};