open JsonWebToken;
open Json_encode;

type tokenRole = {
    email: string,
    pseudo: string,
    name: string,
    surname: string,
    userRole: string,
  
};

module Decoder = {
    let decodeToken = json =>
      Json.Decode.{
        userRole: json |> field("userRole", string),
        email: json |> field("email", string),
        pseudo: json |> field("pseudo", string),
        name: json |> field("name", string),
        surname: json |> field("surname", string),
      };

    let decryptToken = (token) => {
        decode(token);
    }
};