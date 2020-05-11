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
    background-color:#F2EFEF;
  }
  .forumButton button{
    font-size: 15px;
    border-radius : 5px;
    background-color : #F2EFEF;
    padding : 5px;
    float:left;
  }
  .accueilButton button{
    font-size: 15px;
    border-radius : 5px;
    background-color : #F2EFEF;
    padding : 5px;
    margin-bottom : 10px;
  }
  .accueilButton{
    margin-bottom : 10px;
  }
  .all{
    display : inline-block;
  }

  .allCours, .fo{
    position : absolute;
    background-color : #F2EFEF;
    width: 80%;

  }
  .fo{
    z-index:1;
    left : 75%;
    width : 17%;
  }
  .maskFo{
    position:absolute;
  }

  .maskFo{
    margin-top : 15px;
    margin-left:135px;
    font-size: 15px;
    border-radius : 5px;
    background-color : #F2EFEF;
    padding : 5px;
  }

|j};