let reasonReactBlue = "#48a9dc";

// The {j|...|j} feature is just string interpolation, from
// bucklescript.github.io/docs/en/interop-cheatsheet#string-unicode-interpolation
// This allows us to conveniently write CSS, together with variables, by
// constructing a string
let style = {j|
  
  .theForum{
    background-color: rgb(224, 226, 229);
    display: flex;
    flex-direction: column;
    align-items: center;
    float:right;
    clear:right;
    margin-right:2%;
    margin: 12px 0px;
    float:right;
    box-shadow: 0px 4px 16px rgb(200, 200, 200);
    clear right;
    width: 500px; 
    border-radius: 12px;
    font-family: sans-serif;
    height: 800px;
  }

  .raffraichir, .envoyer{
    background-color: white;
    color: $reasonReactBlue;
    float:right;
    clear:right;
    text-decoration:none;
    font-weight:bold;
    font-size:18px;
    color:#799dec;
    border:none;
    background-color:white;
    text-shadow:0px 4px 2px rgba(0, 0, 0, 0.32), 0px 1px 0px #6182ca, 0px 2px 0px #4f6aa7, 0px 3px 0px #5470ad;
  }

  .raffraichir:active, .envoyer:active{
    background-color: $reasonReactBlue;
    color: white;
  }
|j};