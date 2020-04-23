let reasonReactBlue = "#48a9dc";

// The {j|...|j} feature is just string interpolation, from
// bucklescript.github.io/docs/en/interop-cheatsheet#string-unicode-interpolation
// This allows us to conveniently write CSS, together with variables, by
// constructing a string
let style = {j|
  
form{
    margin-left:39.5%;
    margin-top:50px;
}

.title, .description, .video, .modules{
    margin-bottom : 20px;
}

.title input, .description input, .video input, .modules input{
    border-radius : 3px;
    width:20%;
    height:20px;
}

.title label, .description label , .video label, .modules label{
    display:block;
}

.retour{
    margin-left: 30%;
}

.ajoutCours input{
	padding:6px 0 6px 0;
	font:bold 13px Arial;
	background:#f5f5f5;
	color:#555;
	border-radius:2px;
	width:100px;
	border:1px solid #ccc;
    margin-bottom : 20px;
    cursor: pointer;
    margin-left : 62px;

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