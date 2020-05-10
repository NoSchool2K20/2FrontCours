[@bs.val] external document: Js.t({..}) = "document";

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= ForumStyle.style;

[@react.component]
let make = (~token, ~titleCours) => {

  <>
      <div className="theForum">
              <div> 
          {React.string("Forum")}
        </div>
        <DisplayMessages cours=titleCours user=token />
      </div>
  </>;
};