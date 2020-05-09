open AssignmentRequest;
open AssignmentRequests;
open User;
[@bs.val] external atob: string => Js.String.t = "atob";
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
           {React.string("Aucune demande d'élévation pour le moment.")}
         </div>
       | _ =>
        <div className="elevationList">
        <div className="titleElevation">  {React.string("Toutes les demandes")} </div>
              (
                React.array(Array.of_list(
                    List.map((p) =>
                    <div className="elevation"> {React.string(AssignmentRequest.getEmailUserForAssignment(p))} 
                    <button onClick={(_) => {acceptElevation(AssignmentRequest.getAssignmentRequestId(p));();}}>
                          {React.string("Accepter")}
                    </button>
                    <button onClick={(_) => {refuseElevation(AssignmentRequest.getAssignmentRequestId(p));();}}>
                          {React.string("Refuser")}
                    </button>
                    </div>
                    , stateAssignment)
                ))
              )
        </div>
       }}
    </div>
    </>

    };