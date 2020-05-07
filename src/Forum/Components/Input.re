[@bs.val] external fetch: string => Js.Promise.t('a) = "fetch";
let inputStyle = ReactDOMRe.Style.make( ~padding="10px", ~marginTop="30px", ());

[@react.component]
let make = _ => {
    let (name, setName) = React.useState(() => "");

    let onChange = (e: ReactEvent.Form.t): unit => {
      let value = e->ReactEvent.Form.target##value;
      setName(value);
    };
  
    let onSubmit = (e: ReactEvent.Form.t): unit => {
      ReactEvent.Form.preventDefault(e);
      let payload=Js.Dict.empty();
             Js.Dict.set(payload, "idCours", Js.Json.string("POO"));
             Js.Dict.set(payload, "auteur", Js.Json.string("monUser"));
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

    <form onSubmit>
      <input style=inputStyle placeholder="Votre message" type_="text"name="name" value=name onChange/>
      <button type_="submit">{ReasonReact.string("Envoyer")} </button>
      </form>
      
};