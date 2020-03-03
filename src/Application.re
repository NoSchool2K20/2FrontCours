[@bs.val] external token: string = "process.env.GITHUB_TOKEN";

[@react.component]
let make = _ => {
  let url = ReasonReactRouter.useUrl();
  let innerContent =
    switch (url.path) {
    | [] => <p> {React.string("Welcome on our website")} </p>
    | ["github"] => <Github token />
    | _ =>
      <p>
        <img src="https://media.giphy.com/media/VwoJkTfZAUBSU/giphy.gif" />
      </p>
    };

  let navMenu =
    <>
      <button
        onClick={_ => ReasonReactRouter.push("/")}
        className={url.path == [] ? "selected" : ""}>
        {React.string("Home")}
      </button>
      <button
        onClick={_ => ReasonReactRouter.push("/github")}
        className={url.path == ["gihub"] ? "selected" : ""}>
        {React.string("My Github")}
      </button>
    </>;

  <>
    <h1> {React.string("Menu")} </h1>
    <div> navMenu </div>
    <div className="content"> innerContent </div>
  </>;
};