[@bs.val] external document: Js.t({..}) = "document";




let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= DisplayMessagesStyle.style;

open Messages;
[@react.component]
let make = (~cours, ~user) => {
  let (stateMessage, setStateMessage) = React.useState(() => []);
 

  let decodeMessages= json =>
  
    json |> Messageslist.fromJson
  ;


  let getMessagesLists = (cours, user) =>
    Js.Promise.(
      Fetch.fetchWithInit("https://service-forum.cleverapps.io/message?cours=" ++ cours ++ "&userId=" ++ user,
      Fetch.RequestInit.make(~method_=Get, ()),)
      |> then_(Fetch.Response.json)
      |> then_(json  => {
           setStateMessage(_ => List.append(stateMessage, decodeMessages(json)));
           Js.log(stateMessage);
           Js.Promise.resolve();
         })
      |> catch(_err
           => Js.Promise.resolve())
      |> ignore
    );

    React.useEffect0(() => {
      getMessagesLists(cours, user);
      None;
    });
  // Render //
  <div> 
    <button onClick={ _ => ReasonReact.Router.push("/")}>{React.string("Rafraichir")}</button>
  {switch (stateMessage) {
    | [] =>
      <div>

         <p> {React.string("Aucun message, postez-en un!")} </p>
       </div>
    | _ =>
    <div  className="content-main">
     (
      React.array(Array.of_list(
          List.map((p) =>
    <MessageBloc auteur=Messages.getAuteur(p) texte=Messages.getTexte(p) dateenvoi=Messages.getDateEnvoi(p) nblikes=Messages.getNbLikes(p) />
          , stateMessage)
      ))
    )
     </div>

}}
<Input />
  </div>

};
/*
          <div > 
            <p>{React.string(Messages.getTexte(p))}</p>
            <p> {React.string(Messages.getAuteur(p))} </p>
          </div>
          */