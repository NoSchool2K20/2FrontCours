[@bs.val] external token: string = "process.env.GITHUB_TOKEN";

[@react.component]
let make = _ => {
  let url = ReasonReactRouter.useUrl();
  let tok = Dom.Storage.getItem("token", Dom.Storage.localStorage);
   let path = switch (tok) {
    | None => ["connection"]
    | Some("") => ["connection"]
    | Some(token) => url.path
    }

  let innerContent =
    switch (path) {
    | [] => <Home /> 
    | ["connection"] => <Connection /> 
    | ["cours", title] => <CoursPage title=title />
    | ["addCours"] => <AddCours />
    | ["askPrivileges"] => <AskPrivileges />
    | ["acceptPrivileges"] => <AcceptPrivilegesForm />
    | _ =>
      <p>
        <img src="https://media.giphy.com/media/VwoJkTfZAUBSU/giphy.gif" />
      </p>
    };

  <>
    <div className="logo">
      <img
        src="../src/logo.png"
        alt="Logo NoSchool"/>

        /*<div> 
          {React.string("Bienvenue !")}
        </div> */
    </div>
    <div className="content"> innerContent </div>
  </>;
};