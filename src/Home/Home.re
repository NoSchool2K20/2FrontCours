[@bs.val] external token: string = "process.env.GITHUB_TOKEN";
[@bs.val] external document: Js.t({..}) = "document";
[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";
[@bs.val] external atob: string => Js.String.t = "atob";
[@bs.val] external btoa: string => string = "btoa";

[@bs.module "base-64"] external decode: string => Js.String.t = "decode";

open Parcours;
open Parcourslist;
open Module;
open Moduleslist;
open Cours;
open User;

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= HomeStyle.style;

[@bs.deriving abstract]
type jsProps = {

  className: string,
  modules: Moduleslist.t,
  parcours: Parcourslist.t,
  cours: Courslist.t,
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
      Fetch.fetchWithInit("http://18.220.58.155:8080/cours/?module=" ++ title,
      Fetch.RequestInit.make(~method_=Get,
        ~headers=Fetch.HeadersInit.make({"Authorization": "Bearer " ++ getTok()}),()),)
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
      Fetch.RequestInit.make(~method_=Get,
        ~headers=Fetch.HeadersInit.make({"Authorization": "Bearer " ++ getTok()}),()),)
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
      Fetch.RequestInit.make(~method_=Get, 
        ~headers=Fetch.HeadersInit.make({"Authorization": "Bearer " ++ getTok()}),()),)
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

let deco = () => {
  let ls = Dom.Storage.localStorage;
  Dom.Storage.setItem("token","", ls); 
  ReasonReactRouter.push("/connection")
}

let welcome=
<>
  <p>
    //{React.string(body |> atob)}
    {React.string("Welcome " ++ User.getName(decodeToken(jsonbody)))}
  </p>
</>;

  let buttonDroits=
  <>
  <button className="buttonDroits"
    onClick={_ => ReasonReactRouter.push("/askPrivileges")}>
    {React.string("Elevation de privileges")}
  </button>
  </>;

   let acceptDroits=
  <>
  <button className="consultElevations"
    onClick={_ => ReasonReactRouter.push("/acceptPrivileges")}>
    {React.string("Demandes d'elevation")}
  </button>
  </>;

  let buttonDeconnection=
  <>
  <button className="deconnection"
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

  /*-------------------------------------------------------------------------*/

let all = 
  <>
  <div className="buttons">
    buttonDeconnection
    {switch (User.getUserRole(decodeToken(jsonbody))) {
           | "Administrateur"=>
             acceptDroits
           | _ =>
            <p></p>
           }}

    {switch (User.getUserRole(decodeToken(jsonbody))) {
           | "Nouveau"=>
             buttonDroits
           | _ =>
            <p></p>
           }}
    </div>
    <div className="bienvenue"> welcome </div>
    <div>
      {switch (stateParcours) {
       | [] =>
         <div className="parcours"> 
           {React.string("Aucun parcours pour le moment")}
         </div>
       | _ =>
        <div>
        <div className="choseParcours">  {React.string("Nos parcours")} </div>
        <div className="parcoursList">
              (
                React.array(Array.of_list(
                    List.map((p) =>
                    <div className="parcours" onClick={(_) => {getParcoursModules(Parcours.getTitle(p));();}}> {React.string(Parcours.getTitle(p))} </div>
                    , stateParcours)
                ))
              )
        </div>
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
    <div className="buttonAjoutCours"> 
    {switch (User.getUserRole(decodeToken(jsonbody))) {
           | ("Professeur") =>
             buttonAjoutCours
           | ("Administrateur") =>
             buttonAjoutCours
           | _ =>
            <p></p>
           }}
    </div>

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

  <>
  {switch (User.getUserRole(decodeToken(jsonbody))) {
               | "Nouveau" =>
               <div className="buttonNouveau">
                 buttonDroits
                 buttonDeconnection
                <p className="accueilNouveau"> {React.string({j|Vous devez faire une demande d'élévation de privilèges afin d'accéder au contenu du site !|j})} </p>
                </div>
               | _ =>
                all
    }}
  </>
};