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

.elevation input{
	padding:6px 0 6px 0;
	font:bold 13px Arial;
	background:#f5f5f5;
	color:#555;
	border-radius:2px;
	width:150px;
	border:1px solid #ccc;
    cursor: pointer;
    margin-top : 10px;
}

.create{
    padding:6px 0 6px 0;
	font:bold 13px Arial;
	background:#478bf9;
	color:#fff;
	border-radius:2px;
	width:100px;
	border:none;
    margin-left : 62px;
    cursor: pointer
    margin-top : 20px;
}

|j};