let reasonReactBlue = "#48a9dc";

// The {j|...|j} feature is just string interpolation, from
// bucklescript.github.io/docs/en/interop-cheatsheet#string-unicode-interpolation
// This allows us to conveniently write CSS, together with variables, by
// constructing a string
let style = {j|
  .bienvenue{
    text-align : center;
    font-weight : bold;
    padding-top : 55px;
  }

  .accueilNouveau{
    padding-top:70px;
    text-align : center;
  }
  .buttonNouveau button{
    font-size: 15px;
    background-color : #F7F7F7;
    float:right;
    margin : 5px;
    border-radius : 3px;
    height : 31px;
    display:block;
  }

  .buttonPrivileges button{
    font-size: 15px;
    border-radius : 5px;
    background-color : #F7F7F7;
    padding : 5px;
    float : right;
  }

  .buttonDeconnection button{
    font-size: 15px;
    background-color : #F7F7F7;
    float:right;
    margin : 5px;
    border-radius : 3px;
    height : 31px;
  }

  .acceptPrivileges button{
    font-size: 15px;
    background-color : #F7F7F7;
    float:right;
    margin : 5px;
    border-radius : 3px;
    height : 31px;
  }

  .buttons button{
    font-size: 15px;
    background-color : #F7F7F7;
    float:right;
    margin : 5px;
    border-radius : 3px;
    height : 31px;
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
    cursor: pointer;
    display: inline-block;
    align-items : center;
    margin : 5px;
  }

  .parcoursList{
    text-align:center;
  }

  .menuModules{
    border-top : 2px solid Gray;
    text-align : center;
    margin-top : 30px;
    padding-top : 50px;
    padding-bottom : 20px;
  }
  .menuModules button{
    padding-left : 15px;
    padding-right : 15px;
    padding-top : 8px;
    padding-bottom : 8px;
    font-size : 14px;
    border-radius : 5px;
    color : #514714;
  }
  .cours{
    border-radius : 5px;
    text-align : center;
    border-top : 10px;
    border-bottom : 10px;
    margin : 10px;
  }
  .cours .leCours{
    display : inline-block;
    border : 1px solid Gray;
    width : auto;
    border-radius : 5px;
    margin : 5px;
    padding-bottom : 10px;
    background-color: rgb(224, 226, 229);
    height : auto;
    margin-top : 15px;
  }

  .parcoursList{
    height:110px;
    margin-bottom: 50px;
  }

  .choseParcours{
    text-align:center;
    font-size: 24px;
    font-family: arial;
    padding-top:45px;
    color : black;
    font-weight : bold;
  }

  .parcoursList .parcours{
    text-align: center;
    margin-top:30px;
    padding:10px;
    color : #514714;
  }

  .buttonAjoutCours button{
    padding-left : 15px;
    padding-right : 15px;
    padding-top : 8px;
    padding-bottom : 8px;
    font-size : 14px;
    border-radius : 5px;
    background-color : #514714;
    color : white;
  }

  .leCours .titre{
    font-weight : bold;
  }
|j};