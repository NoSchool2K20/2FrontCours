type state = {
    prof:bool,
    etudiant:bool,
    submitted:bool,
    formDisplay:bool,
    error:bool
};

type user = {
    token:string
};

[@bs.val] external document: Js.t({..}) = "document";

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= AddCoursStyle.style;
    
[@react.component]
let make = _ => {

 let getTok = () => {
let tok = Dom.Storage.getItem("token", Dom.Storage.localStorage);
  switch (tok) {
  | None => ""
  | Some(token) => token
  }
  
};    

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
            "Professeur"
        } else if (state.etudiant){
            "Etudiant"
        }
        else{
            ""
        };

        let _ = Js.Promise.(
            Fetch.fetchWithInit(
                "http://127.0.0.1:8080/assignmentRequest",
                Fetch.RequestInit.make(
                    ~method_=Post,
                    ~body=Fetch.BodyInit.make(roleRequest),
                    ~headers=Fetch.HeadersInit.make({"Content-Type":"application/json","Authorization": "Bearer " ++ getTok()}),
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
    <div className="prof form-group mt-1">
        <label htmlFor="prof">"Professeur"->React.string</label>
        <input type_="checkbox" name="prof" className="checkbox" required={false} onChange={_=>{
                setState(state => {
                    ...state, 
                    prof:true
                });
            }}        
        />
    </div>

    <div className="etudiant form-group">
        <label htmlFor="etudiant">"Etudiant"->React.string</label>
        <input type_="checkbox" className="etudiant" name="etudiant" required={false} onChange={_=>{
                setState(state => {
                    ...state,
                    etudiant:true
                });
            }}
        />
    </div>

    <div className="form-group">
        <div className="row">
            <div className="elevation col text-right">
                <input type_="submit" value="Demander l'elevation" className="btn btn-primary"/>
            </div>
        </div>
    </div>

    <div className="col">
                <a type_="button" className="retour text-primary" onClick={_ => {
                        ReasonReactRouter.push("/")
                }}>"Retour"->React.string</a>
    </div>

    {(state.error) ? <div className="form-text text-muted">"Something went wrong, please try again"->React.string</div> : ReasonReact.null}
    
</form>;

<>
    <div > 
        form_askElevation
    </div>
</>

};