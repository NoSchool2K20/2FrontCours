//[@bs.module "uuid"] external uuidv4: unit => string = "v4";

module AssignmentRequest: {
  type t; // this is an abastraction to enforce creation with make functions
  let make: (string, string, string, bool, bool) => t;
  let makeNew: (string, string, bool, bool) => t;
  let getAssignmentRequestId: t => string;
  let getEmailUserForAssignment: t => string;
  let getRoleRequest: t => string;
  let getDecision: t => bool;
  let getProcessed: t => bool;
  let fromJson: Js.Json.t => t;
  let fromJsonWithBoolean: Js.Json.t => t;
  let fromString: string => option(t);
  let toJson: t => Js.Json.t;
  let toString: t => string;
} = {
  type t = {
    assignmentRequestId: string,
    emailUserForAssignment: string,
    roleRequest: string,
    decision: bool,
    processed: bool,
  };

  // create a value of the type AssignmentRequests.t
  let make = (assignmentRequestId, emailUserForAssignment, roleRequest, decision, processed) => {
    {assignmentRequestId, emailUserForAssignment, roleRequest, decision, processed}
  }

  let makeNew = (emailUserForAssignment, roleRequest, decision, processed) => make("", emailUserForAssignment, roleRequest, decision, processed)

  // Getters are mandatory because of abstraction,
  // while it is a good practice for accessing records members, like for object members
  let getAssignmentRequestId = assignmentrequest => assignmentrequest.assignmentRequestId;
  let getEmailUserForAssignment = assignmentrequest => assignmentrequest.emailUserForAssignment;
  let getRoleRequest = assignmentrequest => assignmentrequest.roleRequest;
  let getDecision = assignmentrequest => assignmentrequest.decision;
  let getProcessed = assignmentrequest => assignmentrequest.processed;
  
  let bool_of_int = value => value === 1;

  //let bool_of_int = value => value === 1;
  let fromJson = json =>
    Json.Decode.{
      assignmentRequestId: json |> field("assignmentRequestId", string),
      emailUserForAssignment: json |> field("emailUserForAssignment", string),
      roleRequest: json |> field("roleRequest", string),
      decision: json |> field("decision", int) |> bool_of_int,
      processed: json |> field("processed", int) |> bool_of_int,
    };

let fromJsonWithBoolean = json =>
    Json.Decode.{
      assignmentRequestId: json |> field("assignmentRequestId", string),
      emailUserForAssignment: json |> field("emailUserForAssignment", string),
      roleRequest: json |> field("roleRequest", string),
      decision: json |> field("decision", bool),
      processed: json |> field("processed", bool),
    };

  let fromString = jsonString =>
    switch (Json.parse(jsonString)) {
    | Some(validJson) => Some(fromJson(validJson))
    | None => None
    };


  let toJson = assignmentrequest =>
    // Json module comes from bs-json, it is not Js.Json module
    // Use of bs-json to encode json in expressive way while you can use Js.Json / Js.Dict in an imperative way
    Json.Encode.(
      object_([
        ("assignmentRequestId", string(assignmentrequest.assignmentRequestId)),
        ("emailUserForAssignment", string(assignmentrequest.emailUserForAssignment)),
        ("roleRequest", string(assignmentrequest.roleRequest)),
        ("decision", bool(assignmentrequest.decision)),
        ("processed", bool(assignmentrequest.processed)),
      ])
    );

  let toString = user => toJson(user) |> Js.Json.stringify;
};

module AssignmentRequests: {
  type t = list(AssignmentRequest.t);
  let fromJson: Js.Json.t => t;
  let fromString: string => option(t);
  let toJson: t => Js.Json.t;
  let toString: t => string;
} = {
  type t = list(AssignmentRequest.t);

  let fromJson: Js.Json.t => t =
    json => json |> Json.Decode.(list(AssignmentRequest.fromJsonWithBoolean));
    

  let fromString = jsonString =>
    switch (Json.parse(jsonString)) {
    | Some(validJson) => Some(fromJson(validJson))
    | None => None
  };

  let toJson = assignmentrequests =>
    Array.of_list(assignmentrequests)  
    |> Array.map(item => AssignmentRequest.toJson(item))  
    |> Json.Encode.jsonArray;
  let toString = assignmentrequests => toJson(assignmentrequests) |> Js.Json.stringify;
};