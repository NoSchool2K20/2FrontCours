open AssignmentRequest;
open AssignmentRequests;
open User;
[@bs.val] external atob: string => Js.String.t = "atob";

[@react.component]
let make = _ => {
let (stateAssignment, setStateAssignment) = React.useState(() => []);
  
let decodeAssignment= json =>
    json |> AssignmentRequests.fromJson
  ;

  let getTok = () => {
let tok = Dom.Storage.getItem("token", Dom.Storage.localStorage);
  switch (tok) {
  | None => ""
  | Some(token) => token
  }
};

let accueil = 
  <>
    <button
        onClick={_ => ReasonReactRouter.push("/")}>
        {React.string("Accueil")}
      </button>
  </>;

  let getAllElevations = () =>
    Js.Promise.(
      Fetch.fetchWithInit("https://noschool-authentication.cleverapps.io/assignmentRequest/notprocessed",
      Fetch.RequestInit.make(~method_=Get,
        ~headers=Fetch.HeadersInit.make({"Authorization": "Bearer " ++ getTok()}),()),)
      |> then_(Fetch.Response.json)
      |> then_(json  => {
        Js.log(json);
           let decoded = decodeAssignment(json);
           Js.log(decoded);
           setStateAssignment(_ => List.append([], decoded));
           Js.Promise.resolve();
         })

      |> catch(_err
           => Js.Promise.resolve())
      |> ignore
    );

 React.useEffect0(() => {
    getAllElevations();
    None;
  });

<>
<div>
    <div className="accueilButton"> accueil </div>

      {switch (stateAssignment) {
       | [] =>
         <div className="noElevations"> 
           {React.string("Aucune demande d'élévation pour le moment.")}
         </div>
       | _ =>
        <div className="elevationList">
        <div className="titleElevation">  {React.string("Toutes les demandes")} </div>
              (
                React.array(Array.of_list(
                    List.map((p) =>
                    <div className="elevation" onClick={(_) => {getAllElevations();();}}> {React.string(AssignmentRequest.getEmailUserForAssignment(p))} </div>
                    , stateAssignment)
                ))
              )
        </div>
       }}
    </div>
    </>

    };