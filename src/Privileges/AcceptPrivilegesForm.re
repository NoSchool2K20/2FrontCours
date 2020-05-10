open AssignmentRequest;
open AssignmentRequests;
open User;
[@bs.val] external atob: string => Js.String.t = "atob";
[@bs.val] external document: Js.t({..}) = "document";

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= AcceptPrivilegesStyle.style;

[@bs.deriving abstract]
type jsProps = {

  assignments: AssignmentRequests.t,
};
[@react.component]
let make = _ => {
let (stateAssignment, setStateAssignment) = React.useState(() => []);
let (stateAccepted, setStateAccepted) = React.useState(() => false);

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
           let decoded = decodeAssignment(json);
           setStateAssignment(_ => List.append([], decoded));
           Js.Promise.resolve();
         })

      |> catch(_err
           => Js.Promise.resolve())
      |> ignore
    );

let acceptElevation = (assignmentRequestId) =>
    Js.Promise.(
            Fetch.fetchWithInit(
                "https://noschool-authentication.cleverapps.io/assignmentRequest/" ++ assignmentRequestId ++ "/accept",
                Fetch.RequestInit.make(
                    ~method_=Post,
                    ~headers=Fetch.HeadersInit.make({"Content-Type":"application/json", "Authorization": "Bearer " ++ getTok()}),
                    ()
                )
            )
            |> then_(Fetch.Response.json)
            |> then_(_ => {
                ReasonReactRouter.push("/acceptPrivileges");
                Js.Promise.resolve();
            })
            |> catch(_ => {
                Js.Promise.resolve();
            })
        );

 React.useEffect0(() => {
    getAllElevations();
    None;
  });

  let refuseElevation = (assignmentRequestId) =>
    Js.Promise.(
            Fetch.fetchWithInit(
                "https://noschool-authentication.cleverapps.io/assignmentRequest/" ++ assignmentRequestId ++ "/decline",
                Fetch.RequestInit.make(
                    ~method_=Post,
                    ~headers=Fetch.HeadersInit.make({"Content-Type":"application/json", "Authorization": "Bearer " ++ getTok()}),
                    ()
                )
            )
            |> then_(Fetch.Response.json)
            |> then_(_ => {
                ReasonReactRouter.push("/acceptPrivileges");
                Js.Promise.resolve();
            })
            |> catch(_ => {
                Js.Promise.resolve();
            })
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
           {React.string({j|"Aucune demande d'élévation pour le moment.|j})}
         </div>
       | _ =>
        <div className="elevationList">
        <div className="titleElevation">  {React.string("Toutes les demandes")} </div>
              (
                React.array(Array.of_list(
                    List.map((p) =>
                    <div className="elevationDiv">
                     <p>{React.string(AssignmentRequest.getEmailUserForAssignment(p) ++ {j| demande à avoir le profil |j}  ++ {j|AssignmentRequest.getRoleRequest(p)|j})}</p> 
                    <button className="accepter" onClick={(_) => {acceptElevation(AssignmentRequest.getAssignmentRequestId(p));();}}>
                          {React.string("Accepter")}
                    </button>
                    <button className="refuser" onClick={(_) => {refuseElevation(AssignmentRequest.getAssignmentRequestId(p));();}}>
                          {React.string("Refuser")}
                    </button>
                    <div className="css"> </div> 
                    </div>
                    , stateAssignment)
                ))
              )
        </div>
       }}
    </div>
    </>

    };