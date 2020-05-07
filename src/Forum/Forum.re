[@react.component]
let make = (~token, ~titleCours) => {

  <>
        <div> 
          {React.string("Forum")}
        </div>
        <DisplayMessages cours=titleCours user=token />
  </>;
};