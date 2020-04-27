/*open Root;

let component = ReasonReact.reducerComponent("App");

let divprinc =
ReactDOMRe.Style.make(
  ~float="right",
  ~clear="right",
  ~border="2px solid #898989",
  ~borderRadius="4px",
  ~padding="1rem",
  ~width="500px",
  ~height="1000px",
  ~overflow="auto",
  (),
);
let make = _children => {
  ...component,
  initialState: () => initialAppState,
  reducer,
  render: ({state, send}) =>
    <div style=divprinc>
      <Form ctx={input:"in", utilisateur:"1"} appSend=send />
      <SendMessage ctx={input:"in", utilisateur:"1",text:state.text} appSend=send />
      <Results ctx={ results: state.results }utilisateur="1" appSend=send/>
    </div>,
};*/