let reasonReactBlue = "#48a9dc";

// The {j|...|j} feature is just string interpolation, from
// bucklescript.github.io/docs/en/interop-cheatsheet#string-unicode-interpolation
// This allows us to conveniently write CSS, together with variables, by
// constructing a string
let style = {j|
  .parcours{
    margin: 0 auto;
    width: 100px;
    text-align: center;
    background-color: #DDA0DD;
    border-radius: 10px;
    padding: 1%
  }
|j};