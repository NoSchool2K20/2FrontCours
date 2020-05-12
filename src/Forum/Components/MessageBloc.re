[@bs.val] external document: Js.t({..}) = "document";

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= MessageBlocStyle.style;
type state = {
    count: int,
    hasLiked: bool,
    hasdel: bool
};

type action =
  | Increment
  | Decrement
  | Delete;

[@react.component]
let make = (~texte, ~auteur, ~dateenvoi, ~nblikes, ~idMessage, ~isLiked, ~utilisateur) => {
    let initialState = {count: int_of_string(nblikes), hasLiked: {React.string(isLiked)} !== {React.string("0")}, hasdel: false};
    let reducer = (state, action) => {
    switch (action) {
    | Increment => {count: state.count + 1, hasLiked : true, hasdel: false}
    | Decrement => {count: state.count - 1, hasLiked : false, hasdel: false}
    | Delete =>  {count: state.count, hasLiked : false, hasdel: true}
    };
    };
    let (state, dispatch) = React.useReducer(reducer, initialState);
    let suppr = () => {
        dispatch(Delete);
          let payload=Js.Dict.empty();
         Js.Dict.set(payload, "idMessage", Json.Encode.int(int_of_string(idMessage)));
          Js.Promise.(
            Fetch.fetchWithInit(
              "https://service-forum.cleverapps.io/message",
              Fetch.RequestInit.make(
                ~method_=Delete,
                ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
                ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
                ()
              )
            )
            |> then_(Fetch.Response.json)
            |> ignore             
          )
                 
      };

      let like= () => {
        dispatch(Increment);
        let payload=Js.Dict.empty();
        Js.Dict.set(payload, "idMessage", Json.Encode.int(int_of_string(idMessage)));
        Js.Dict.set(payload, "userId", Js.Json.string({utilisateur}));
         Js.Promise.(
           Fetch.fetchWithInit(
             "https://service-forum.cleverapps.io/like",
             Fetch.RequestInit.make(
               ~method_=Post,
               ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
               ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
               ()
             )
           )
           |> then_(Fetch.Response.json)
           |> ignore             
           )
      };

      let dislike= () => {
        dispatch(Decrement);
        let payload=Js.Dict.empty();
        Js.Dict.set(payload, "idMessage", Json.Encode.int(int_of_string(idMessage)));
        Js.Dict.set(payload, "userId", Js.Json.string({utilisateur}));
         Js.Promise.(
           Fetch.fetchWithInit(
             "https://service-forum.cleverapps.io/like",
             Fetch.RequestInit.make(
               ~method_=Delete,
               ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
               ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
               ()
             )
           )
           |> then_(Fetch.Response.json)
                        |> ignore             
                )    
      };
      let content_del = 
      if ({React.string(auteur)} == {React.string(utilisateur)}) {
        <img className="delimg" 
        src="http://www.myiconfinder.com/uploads/iconsets/256-256-8796bc16719a5e8bbaa44561df7ee979.png" 
        onClick={ _ => suppr()}/>
    } else {
          <p></p>
      };

      let content_like = 
      if ({React.string(auteur)} != {React.string(utilisateur)}) {
          if (state.hasLiked == false) {
            <img className="likeimg" 
            src="https://upload.wikimedia.org/wikipedia/commons/thumb/6/6e/OOjs_UI_icon_heart.svg/1200px-OOjs_UI_icon_heart.svg.png" 
            title="+1"
            onClick={ _ => like()}/>

          } else {
            <img className="likeimg" 
            src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/c8/Love_Heart_symbol.svg/1111px-Love_Heart_symbol.svg.png"
            title="-1"
            onClick={ _ => dislike()} />

          }
      } else {
          <p></p>
      };
      let content_mess = 
      if(state.hasdel == false) {
        <div className="allMessage">
        
        <div className="info">
        <img className="user" 
    src="https://upload.wikimedia.org/wikipedia/commons/1/12/User_icon_2.svg"
 />
        <p className="auteur">{React.string(auteur)}</p> 
        <p className="date">{React.string(dateenvoi)}</p>
        content_del
        content_like
        <p className="likes">{React.string(string_of_int(state.count))}</p>
        </div>
        <p className="texte">{React.string(texte)}</p>
        </div>;
      } else {
          <div></div>
      };


      content_mess
   
};