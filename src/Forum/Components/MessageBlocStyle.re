// The {j|...|j} feature is just string interpolation, from
// bucklescript.github.io/docs/en/interop-cheatsheet#string-unicode-interpolation
// This allows us to conveniently write CSS, together with variables, by
// constructing a string
let style = {j|
.content {
    border: 1px solid grey;
    broder-radius: 8px;
    background-color: #FAFAFA;
    margin: 15px;
    padding: 0px 15px;
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
  }

|j};