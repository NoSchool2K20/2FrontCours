let reasonReactBlue = "#48a9dc";

// The {j|...|j} feature is just string interpolation, from
// bucklescript.github.io/docs/en/interop-cheatsheet#string-unicode-interpolation
// This allows us to conveniently write CSS, together with variables, by
// constructing a string
let style = {j|
  
form{
    margin-top:50px;
}

.prof{
    margin-bottom : 5px;
    width : 150px;
}

.retour{
    margin-left: 30%;
}

.submitElevation{
    font-size: 15px;
    background-color : #F7F7F7;
    border-radius : 3px;
    height : 31px;
	width : 175px;
	margin-top : 10px;
}

.elevation{
	width : 100px;
}

|j};