/*Random.self_init();

type ctx = {
  results: Root.list_of_repos,
};

let component = ReasonReact.statelessComponent("Results");

let make = (~ctx: ctx, ~utilisateur,~appSend,_children) => {
  ...component,
  render: _self =>
    <div>
      {
       
          ctx.results
          /* Map each list item to a <Card /> component
               We are using the List.mapi method, which provides
               us with an index argument that we need to uniquely
               define our ids.
             */
          |> List.mapi(
               (index: int, { idmessage, texte, dateenvoi,idcours,auteur,nblikes,isliked}: Root.repository) =>
               <Card key={string_of_int(index)} idmessage texte dateenvoi idcours auteur nblikes isliked
                appSend utilisateur/>
             )
          /* covert to Array before going to DOM */
          |> Array.of_list
          /* Transform the array into a valid React node, similar to ReasonReact.string */
          |> ReasonReact.array
      }
    </div>,
};*/