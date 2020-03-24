[@react.component]
let make = (~name, ~children) => {
  <div>
    <p> {React.string("Hello, " ++ name)} </p>
    children
  </div>
};