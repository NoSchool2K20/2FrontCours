[@bs.val] external token: string = "process.env.GITHUB_TOKEN";
[@bs.val] external document: Js.t({..}) = "document";
[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";

open ReasonUrql;
open Hooks;
open Parcours;
open Parcourslist;
open Module;

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= HomeStyle.style;

//[@bs.deriving jsConverter]
//type modules = {title: string};

[@bs.deriving abstract]
type jsProps = {
  /* some example fields */
  className: string,
  //modules: array(modules),
  parcours: Parcourslist.t,

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

  let decodeParcours= json =>
    json |> Parcourslist.fromJson
  ;

  let decodeModules= json =>
    json |> Moduleslist.fromJson
  ;

  // Requests API
  let parcoursList = () =>
    Js.Promise.(
      Fetch.fetchWithInit("http://18.220.58.155:8080/parcours",
      Fetch.RequestInit.make(~method_=Get, ()),)
      |> then_(Fetch.Response.json)
      |> then_(json  => {
           let decoded = decodeParcours(json);
           setStateParcours(_ => List.append(stateParcours, decoded));
           Js.Promise.resolve(List.append(stateParcours, decoded));

         })
      /*|> catch(_err
           Js.Promise.resolve()
      |> ignore*/
    );

  let getParcoursModules = (title) =>
    Js.Promise.(
      Fetch.fetchWithInit("http://18.220.58.155:8080/module/?parcours=" ++ title,
      Fetch.RequestInit.make(~method_=Get, ()),)
      |> then_(Fetch.Response.json)
      |> then_(json  => {
           let decoded = decodeModules(json);
           setStateModules(_ => List.append(stateModules, decoded));
           Js.Promise.resolve();

         })
      /*|> catch(_err
           Js.Promise.resolve()
      |> ignore*/
    );

  let getModuleCours = () =>
    Js.Promise.(
      Fetch.fetchWithInit("",
      Fetch.RequestInit.make(~method_=Get, ()),)
      |> then_(Fetch.Response.text)
      |> then_(text  => {
           Js.log(text );
            //setStateParcours([|"p"|]);
           Js.Promise.resolve();
         })
      |> catch(_err
           // setter(_previousState => []);
           => Js.Promise.resolve())
      |> ignore
    );

  // let message = Client.make(~url="", ~fetchOptions, ());

  //let parcoursList = Array.make(~url="localhost", ~fetchOptions, ());
  React.useEffect0(() => {
    parcoursList();
    getParcoursModules("MIAGE");
    None;
  });

  // Render //

  let welcome = <> <p> {React.string("BIENVENUE !")} </p> 
  <p> {React.string("Choisissez votre parcours : ")} </p></>;

  let buttonDeconnection=
  <>
  <button
    onClick={_ => ReasonReactRouter.push("/connection")}>
    {React.string("Deconnection")}
  </button>
  </>

  //Récupérer les modules ici
  /*let make = children =>
    ReasonReact.wrapJsForReason(
      ~reactClass=myJSReactClass,
      ~props=jsProps(~className="module", ~modules=stateModules),
      children,
    );*/
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
    <div className="buttonDeconnection"> buttonDeconnection </div>
    <div className="bienvenue"> welcome </div>
    <div>
      {switch (stateParcours) {
       | [] =>
         <div className="parcours"> 
           {React.string("Aucun parcours pour le moment")}
         </div>
       | _ =>
        <div className="parcoursList">
              (
                React.array(Array.of_list(
                    List.map((p) =>
                    <div className="parcours" /*onClick={_ => getParcoursModules(Parcours.getTitle(p))}*/> {React.string(Parcours.getTitle(p))} </div>
                    , stateParcours)
                ))
              )
        </div>
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
