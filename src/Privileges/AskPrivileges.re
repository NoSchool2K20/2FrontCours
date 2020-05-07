type state = {
    prof:bool,
    etudiant:bool,
    submitted:bool,
    formDisplay:bool,
    error:bool
};

let toJson = roleRequest =>
    // Json module comes from bs-json, it is not Js.Json module
    // Use of bs-json to encode json in expressive way while you can use Js.Json / Js.Dict in an imperative way
    Json.Encode.(
        ("roleRequest", string(roleRequest))
    );

[@bs.val] external document: Js.t({..}) = "document";

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= AskPrivilegesStyle.style;
    
[@react.component]
let make = _ => {

 let getTok = () => {
let tok = Dom.Storage.getItem("token", Dom.Storage.localStorage);
  switch (tok) {
  | None => ""
  | Some(token) => token
  }
};   

let accueil = 
  <>
    <button
        onClick={_ => ReasonReactRouter.push("/")}>
        {React.string("Accueil")}
      </button>
  </>;

let (state, setState) = React.useState(()=> {
    prof: false,
    etudiant: false,
    submitted: false,
    formDisplay:true,
    error: false
});


let form_askElevation = 
<form className="formCours container card mt-1"
    onSubmit={event => {
    ReactEvent.Form.preventDefault(event);
    setState(state => {
        ...state,
        submitted: true
    });

       let roleRequest = if (state.prof) {
            Json.Encode.(object_([("roleRequest", string("Professeur"))]));
        } else if (state.etudiant){
            Json.Encode.(object_([("roleRequest", string("Etudiant"))]));

        }
        else{
            Json.Encode.(object_([("roleRequest", string(""))]));

        };

        let _ = Js.Promise.(
            Fetch.fetchWithInit(
                "https://noschool-authentication.cleverapps.io/assignmentRequest",
                Fetch.RequestInit.make(
                    ~method_=Post,
                    ~body=Fetch.BodyInit.make(Js.Json.stringify(roleRequest)),
                    ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json", "Authorization": "Bearer " ++ getTok()}),
                    ()
                )
            )
            |> then_(Fetch.Response.json)
            |> then_(_ => {
                setState(_ => {
                    prof: false, etudiant: false, submitted: false, formDisplay:false, error: false
                });
                ReasonReactRouter.push("/");
                Js.Promise.resolve();
            })
            |> catch(_ => {
                setState(_ => {
                    ...state,
                    error: true
                });
                Js.Promise.resolve();
            })
        );
    

}}>
    <div className="prof">
        <label htmlFor="prof">"Professeur"->React.string</label>
        <input type_="checkbox" name="prof" className="checkbox" required={false} onChange={_=>{
                setState(state => {
                    ...state, 
                    prof:true
                });
            }}        
        />
    </div>

    <div className="etudiant">
        <label htmlFor="etudiant">"Etudiant"->React.string</label>
        <input type_="checkbox" className="etudiant" name="etudiant" required={false} onChange={_=>{
                setState(state => {
                    ...state,
                    etudiant:true
                });
            }}
        />
    </div>

            <div className="elevation">
                <input type_="submit" value="Demander l'elevation" className="btn btn-primary"/>
            </div>
    

                <a type_="button" className="retour text-primary" onClick={_ => {
                        ReasonReactRouter.push("/")
                }}>"Retour"->React.string</a>

    {(state.error) ? <div className="form-text text-muted">"Something went wrong, please try again"->React.string</div> : ReasonReact.null}
    
</form>;

<>
    <div className="accueilButton"> accueil </div>
    <div > 
        form_askElevation
    </div>
</>

};