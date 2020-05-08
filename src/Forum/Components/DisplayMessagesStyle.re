// The {j|...|j} feature is just string interpolation, from
// bucklescript.github.io/docs/en/interop-cheatsheet#string-unicode-interpolation
// This allows us to conveniently write CSS, together with variables, by
// constructing a string
let style = {j|
.content-main {

    overflow-y: scroll;
    float:right;
    clear:right;
    height: 570px;
    width: 100%;    

margin-top: 5%;
}
.message {
    marginTop:10px;
    padding:10px;
    float:right;
    width:440px;
    clear:right;
    size:200px;
    margin-right:2%;
    border:1px solid grey;
    border-radius:8px;
    height:80px;
    box-shadow:10px 5px 5px blue;
}
.texte{
    width:95%;
    height:80%;
    border:none;
    resize:none;
}


|j};