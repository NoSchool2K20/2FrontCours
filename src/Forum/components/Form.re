[@bs.module "../img/user.png"]
external logo : string = "default";
type ctx = {input: string,utilisateur:string};
let bouton=ReactDOMRe.Style.make(~float="right",~clear="right",
~textDecoration="none",
    ~fontWeight= "bold",
    ~fontSize="18px",
    ~color="#799dec",
    ~border="none",
    ~backgroundColor="white",
    ~textShadow="0px 4px 2px rgba(0, 0, 0, 0.32), 0px 1px 0px #6182ca, 0px 2px 0px #4f6aa7, 0px 3px 0px #5470ad",());
let image=ReactDOMRe.Style.make(
  ~visibility="hidden",
  ~height="1px",
  ~width="1px",  ());

  let title=ReactDOMRe.Style.make(
  ~fontSize= "xxx-large",
  ~textAlign="center",
    ());

[@react.component]

//let component = ReasonReact.statelessComponent("Form");

module Styles = {
  let card =
    ReactDOMRe.Style.make(
      ~float="right",
      ~clear="right",
      ~border="2px solid #898989",
      ~borderRadius="4px",
      ~padding="1rem",
      (),
    );
};

let make = (~ctx: ctx, ~appSend, _children) => {
  //...component,
  //render: _self =>
  let form = 
    <form
    
      onSubmit={
        ev => {
          ReactEvent.Form.preventDefault(ev);
          appSend(Root.UpdateInput({ctx.input},{ctx.utilisateur}));
          appSend(Root.Search);
        }
      }>
      <h1 style=title> {ReasonReact.string("Forum "++ ctx.input)} </h1>
           <button style=bouton type_="submit"> {ReasonReact.string("Refresh")} </button>
           <img 
           style=image
           src=logo
           alt= ""
           onLoad={
            ev => {
              appSend(Root.UpdateInput({ctx.input},{ctx.utilisateur}));
              appSend(Root.Search);
            }
          }
           />
    </form>;

    <>
    <div className="form">
    form
    </div>
  </>;
};