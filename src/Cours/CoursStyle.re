let reasonReactBlue = "#48a9dc";

// The {j|...|j} feature is just string interpolation, from
// bucklescript.github.io/docs/en/interop-cheatsheet#string-unicode-interpolation
// This allows us to conveniently write CSS, together with variables, by
// constructing a string
let style = {j|
  .titreCours, .descriptionCours, .videoCours{
    text-align : center;
  }
  .titreCours{
    font-weight:bold;
    margin-bottom : 4%;
    margin-top : 50px;
    font-size: 20px;
  }
  .descriptionCours{
    margin-bottom:2%;
  }
  .videoCours{
    border : 2px solid black;
    border-radius : 10px;
    padding : 15px;
    background-color:#F7F7F7;
  }
  .forumButton button{
    font-size: 15px;
    border-radius : 5px;
    background-color : #F7F7F7;
    padding : 5px;
    float:right;
  }
  .accueilButton button{
    font-size: 15px;
    border-radius : 5px;
    background-color : #F7F7F7;
    padding : 5px;
    margin-bottom : 10px;
  }
  .accueilButton{
    margin-bottom : 10px;
  }
|j};