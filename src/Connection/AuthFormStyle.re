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

.email{
    margin-bottom : 20px;
}

.email input{
    border-radius : 3px;
    width:20%;
    height:20px;
}

.email label{
    display:block;
}

.mdp{
    margin-bottom : 30px;
}

.mdp input{
    border-radius : 3px;
    width:20%;
    height:20px;

}

.mdp label{
    display:block;
}

.login{
    margin-left: 30%;
}

.login input{
	padding:6px 0 6px 0;
	font:bold 13px Arial;
	background:#f5f5f5;
	color:#514714;
	border-radius:2px;
	width:100px;
	border:1px solid #ccc;
    margin-bottom : 20px;
    cursor: pointer

}

.create{
    padding:6px 0 6px 0;
	font:bold 13px Arial;
	background:#514714;
	color:#fff;
	border-radius:2px;
	width:120px;
	border:none;
    margin-left : 62px;
    cursor: pointer
    margin-top : 20px;
}

###################################################################################

.createMail, .createMdp, .createPseudo, .createName, .createSurname{
    margin-bottom : 20px;
}

.createMail input, .createMdp input, .createPseudo input, .createName input, .createSurname input{
    border-radius : 3px;
    width:20%;
    height:20px;
    margin-bottom: 20px;
}

.createMail label, .createMdp label, .createPseudo label, .createName label, .createSurname label{
    display:block;
}

.submitCreate input{
	padding:6px 0 6px 0;
	font:bold 13px Arial;
	background:#f5f5f5;
	color:#555;
	border-radius:2px;
	width:100px;
	border:1px solid #ccc;
    margin-bottom : 20px;
    cursor: pointer;
}

.submitCreate{
    
}

.retour{
    margin-left: 30%;
    padding:6px 0 6px 0;
	font:bold 13px Arial;
	background:#f5f5f5;
	color:#555;
	border-radius:2px;
	width:100px;
	border:1px solid #ccc;
    margin-bottom : 20px;
    cursor: pointer;
}

|j};