let reasonReactBlue = "#48a9dc";

// The {j|...|j} feature is just string interpolation, from
// bucklescript.github.io/docs/en/interop-cheatsheet#string-unicode-interpolation
// This allows us to conveniently write CSS, together with variables, by
// constructing a string
let style = {j|
  
.titleElevation{
    text-align : center;
    font-weight : bold;
    margin-bottom : 30px;
    font-size : 20px;
}

.elevationDiv{
    text-align:center;
}

.css{
  width   : 50%;  /* or 100px */
  border-bottom:1px solid gray;
  margin : 0 auto;
  margin-top : 20px;
}

.accepter, .refuser{
    margin-left : 20px;
}

button{
    font-size: 15px;
    background-color : #F7F7F7;
    margin : 5px;
    border-radius : 3px;
    height : 31px;
}

|j};