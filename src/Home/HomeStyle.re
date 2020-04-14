let reasonReactBlue = "#48a9dc";

// The {j|...|j} feature is just string interpolation, from
// bucklescript.github.io/docs/en/interop-cheatsheet#string-unicode-interpolation
// This allows us to conveniently write CSS, together with variables, by
// constructing a string
let style = {j|
  .bienvenue{
    text-align : center;
    font-weight : bold;
    margin-top : 40px;
  }
  .buttonDeconnection{
    font-size: 17px;
    border-radius : 10px;
    background-color : #F7F7F7;
    float:right;
  }

  .parcours {
    text-align: center;
    margin-bottom : 20px;
    padding : 25px;
    border-radius : 10px;
    margin : 7px;
    font-size : 20px;
    background-color: gainsboro;
    margin: 0 auto;
    width : 15%;
    align-item:center;
    cursor: pointer;

  }
  .menuModules{
    border-top : 2px solid Gray;
    text-align : center;
    margin-top : 10px;
    padding-top : 30px;
    padding-bottom : 20px;
  }
  .menuModules button{
    padding-left : 15px;
    padding-right : 15px;
    padding-top : 8px;
    padding-bottom : 8px;
    font-size : 14px;
    border-radius : 5px;
  }
  .cours{
    border-radius : 5px;
    text-align : center;
    border-top : 10px;
    border-bottom : 10px;
    margin : 10px;
  }
  .cours div{
    display : inline-block;
    border : 1px solid Gray;
    width : 20%;
    border-radius : 5px;
    margin : 5px;
    padding-bottom : 10px;
    background-color: rgb(224, 226, 229);
  }

  .parcoursList{
    height:110px;
    margin-bottom: 30px;
  }

  .parcoursList .choseParcours{
    text-align:center;
    font-size: 24px;
    font-family: arial;
    padding-top:30px;
  }

  .parcoursList .parcours{
    text-align: center;
    margin-top:30px;
    padding:10px;
  }
|j};