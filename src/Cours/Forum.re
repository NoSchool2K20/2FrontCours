[@react.component]
let make = (~token, ~titleCours, ~children) => {
  <div>
    <p> {React.string("Hello World")} </p>
    children
  </div>
};