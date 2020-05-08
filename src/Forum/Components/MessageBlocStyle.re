// The {j|...|j} feature is just string interpolation, from
// bucklescript.github.io/docs/en/interop-cheatsheet#string-unicode-interpolation
// This allows us to conveniently write CSS, together with variables, by
// constructing a string
let style = {j|
.content {
  margin-top: 10px;
padding: 5px;
float: right;
clear: right;
border: 1px solid grey;
border-radius: 8px;
width: 95%;
margin-right: 2%;
}
  .auteur{
    font-size: 15px;
    border-radius : 5px;
    background-color : #F7F7F7;
    padding : 5px;
  }
  .info {
    display: flex;
    align-items: center;
    width: 100%;
  }
  .date {
      color:grey;
      font-size: 0.6em;
    font-weight: bold;
  }
  .likes {
    margin-left: auto;
    margin-right: 2%;
  }
  .delimg {
    height: 20px;
    margin-left: 20px;
    cursor: pointer;
  }
  .likeimg {
    margin-left: 35%;
    height: 20px;
    cursor: pointer;
    float: right;
    clear: right;
    margin-right: 2%;
  }
  .user{
    clear: left;
    float: left;
    margin-right: 3%;
    width: 50px;
    clip-path: ellipse(50% 50% at center center);
  }
.texte{
  width: 100%;

height: 80%;

border: none;

resize: none;

margin-left: 3%;
}
|j};