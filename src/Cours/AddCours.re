type state = {
    title:string,
    description:string,
    submitted:bool,
    formDisplay:bool,
    video_url:string,
    modules:string,
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
    
let (state, setState) = React.useState(()=> {
    title: "",
    description: "",
    submitted: false,
    formDisplay:true,
    video_url: "",
    modules: "",
    error: false
});


let form_cours = 
<form className="formCours container card mt-1"
    onSubmit={event => {
    ReactEvent.Form.preventDefault(event);
    setState(state => {
        ...state,
        submitted: true
    });
    if(state.title != "" && state.description != "" && state.video_url != "" && state.modules != ""){
        let payload = Js.Dict.empty();
        Js.Dict.set(payload, "title", Js.Json.string(state.title));
        Js.Dict.set(payload, "description", Js.Json.string(state.description));
        Js.Dict.set(payload, "video_url", Js.Json.string(state.video_url));
        Js.Dict.set(payload, "modules", Js.Json.string(state.modules));

        let _ = Js.Promise.(
            Fetch.fetchWithInit(
                "http://18.220.58.155:8080/cours",
                Fetch.RequestInit.make(
                    ~method_=Post,
                    ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
                    ~headers=Fetch.HeadersInit.make({"Content-Type":"application/json"}),
                    ()
                )
            )
            |> then_(Fetch.Response.json)
            |> then_(_ => {
                setState(_ => {
                    title: "", description: "", submitted: false, formDisplay:false, video_url: "", modules: "", error: false
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
    
    }
}}>
    <div className="title form-group mt-1">
        <label htmlFor="title">"Titre"->React.string</label>
        <input name="title" className="form-control" value={state.title} required={true} onChange={event=>{
                let title = ReactEvent.Form.target(event)##value;
                setState(state => {
                    ...state, 
                    title:title
                });
            }}        
        />
    </div>

    <div className="description form-group">
        <label htmlFor="description">"Description"->React.string</label>
        <input type_="description" className="form-control" name="description" value={state.description} required={true} onChange={event=>{
                let description = ReactEvent.Form.target(event)##value;
                setState(state => {
                    ...state,
                    description:description
                });
            }}
        />
    </div>

    <div className="video form-group">
        <label htmlFor="video">"Url de la video"->React.string</label>
        <input type_="video" className="form-control" name="video" value={state.video_url} required={true} onChange={event=>{
                let video = ReactEvent.Form.target(event)##value;
                setState(state => {
                    ...state,
                    video_url:video
                });
            }}
        />
    </div>

    <div className="modules form-group">
        <label htmlFor="modules">"Module"->React.string</label>
        <input type_="modules" className="form-control" name="modules" value={state.modules} required={true} onChange={event=>{
                let modules = ReactEvent.Form.target(event)##value;
                setState(state => {
                    ...state,
                    modules:modules
                });
            }}
        />
    </div>

    <div className="form-group">
        <div className="row">
            <div className="ajoutCours col text-right">
                <input type_="submit" value="Ajouter le cours" className="btn btn-primary"/>
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
        form_cours
    </div>
</>

};