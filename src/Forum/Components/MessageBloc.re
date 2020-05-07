[@bs.val] external document: Js.t({..}) = "document";




let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= MessageBlocStyle.style;

[@react.component]
let make = (~texte, ~auteur, ~dateenvoi, ~nblikes) => {
    <div className="content">
    <div className="info">
    <p className="auteur">{React.string(auteur)}</p> 
    <p className="date">{React.string(dateenvoi)}</p>
    <p className="likes">{React.string(nblikes)}</p>
    </div>
    <p className="texte">{React.string(texte)}</p>
    </div>
};