[@bs.val] external document: Js.t({..}) = "document";


let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= DisplayMessagesStyle.style;

open MessagesForFront;

[@react.component]
let make = (~cours, ~user) => {
  let (stateMessage, setStateMessage) = React.useState(() => []);
  let (name, setName) = React.useState(() => "");

  let decodeMessages= json =>
    json |> MessagesForFrontlist.fromJson
  ;

  let getMessagesLists = (cours, user) =>
    Js.Promise.(
      Fetch.fetchWithInit("https://service-forum.cleverapps.io/message?cours=" ++ cours ++ "&userId=" ++ user,
      Fetch.RequestInit.make(~method_=Get, ()),)
      |> then_(Fetch.Response.json)
      |> then_(json  => {
           setStateMessage(_ => List.append(stateMessage, decodeMessages(json)));
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

    // INPUT //

    let onChange = (e: ReactEvent.Form.t): unit => {
      let value = e->ReactEvent.Form.target##value;
      setName(value);
    };
  
    let onSubmit = (e: ReactEvent.Form.t): unit => {
      ReactEvent.Form.preventDefault(e);
      let payload=Js.Dict.empty();
       Js.Dict.set(payload, "idCours", Js.Json.string(cours));
       Js.Dict.set(payload, "auteur", Js.Json.string(user));
       Js.Dict.set(payload, "texte", Js.Json.string(name));
        Js.Promise.(
        Fetch.fetchWithInit(
          "https://service-forum.cleverapps.io/message",
          Fetch.RequestInit.make(
            ~method_=Post,
            ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
            ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
            ()
          )
        )
        |> then_(Fetch.Response.json)
        |> then_(_ => {
              setName(_ => "");
              ReasonReactRouter.push("");
              Js.Promise.resolve();
          })
        |> ignore       
      )
    
    };
  // Render //
  <div> 
    <form className="message" onSubmit>
      <textarea className="texte" placeholder="Votre message" type_="text"name="name" value=name onChange/>
      <button type_="submit">{ReasonReact.string("Envoyer")} </button>
      </form>
      
  {switch (stateMessage) {
    | [] =>
      <div>

         <p> {React.string("Aucun message, postez-en un!")} </p>
       </div>
    | _ =>
    <div  className="content-main" onChange>
     (
      React.array(Array.of_list(
          List.map((p) =>
    <MessageBloc isLiked=MessagesForFront.isLiked(p) 
    utilisateur=user 
    idMessage=MessagesForFront.getIdMessage(p) 
    auteur=MessagesForFront.getAuteur(p) 
    texte=MessagesForFront.getTexte(p) 
    dateenvoi=MessagesForFront.getDateEnvoi(p) nblikes=MessagesForFront.getNbLikes(p) />
          , stateMessage)
      ))
    )
     </div>

}}
  </div>

};

          /*<div > 
            <p>{React.string(Messages.getTexte(p))}</p>
            <p> {React.string(Messages.getAuteur(p))} </p>
          </div>
          */