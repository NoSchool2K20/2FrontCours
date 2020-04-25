let reasonReactBlue = "#48a9dc";

// The {j|...|j} feature is just string interpolation, from
// bucklescript.github.io/docs/en/interop-cheatsheet#string-unicode-interpolation
// This allows us to conveniently write CSS, together with variables, by
// constructing a string
let style = {j|
  body {
    display: flex;
    flex-direction: column;
    align-items: center;
  }
  button:hover {
    cursor: pointer
  }
  .selected {
    color: white;
  }

.container {
    width: 1080px;
    border-radius: 12px;
    font-family: sans-serif;
    background-color : #F7F7F7;
  }
  .containerTitle {
    background-color: rgb(242, 243, 245);
    border-radius: 12px 12px 12px 12px;
    padding: 12px;
    font-weight: bold;
  }
  .containerContent {
    background-color: #F7F7F7;
    border-radius: 12px 12px 12px 12px;
  }
  
  .accueilConnection{
    text-align:center;
  }

  .logo{
    height: 150px;
    background-color:darkgray;
    border-radius: 12px 12px 0px 0px;
  }

  .logo img{
    margin-top:30px;
    margin-left:30px;
  }

  .logo div{
    display : inline-block;
    margin-left : 20%;
    color: #FFF5EE;
    font-size: 28px;
    margin-bottom: 20px;
  }
|j};