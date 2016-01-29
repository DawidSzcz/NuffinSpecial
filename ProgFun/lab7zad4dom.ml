(*Dawid Szczyrk*)

(*4*)
module type DICTIONARY = 
  sig
    type key
    type 'a t
    exception DuplicatedKey of key      (* error in insert *)
    val empty: unit -> 'a t
    (* empty dictionary *)
    val lookup: 'a t -> key -> 'a option
    val insert: 'a t -> key * 'a -> 'a t
    val delete: 'a t -> key -> 'a t  
    val update: 'a t -> key * 'a -> 'a t
  (* not necessary *)
  end;;

type order = LESS | EQUAL | GREATER;;

module type ORDER = sig 
    type t 
    val compare : t-> t -> order 
end
module StringOrder: ORDER with type t = string =
					  struct
					    type t = string
					    let compare s1 s2 = if s1<s2 then LESS else 
								  if s1>s2 then GREATER else EQUAL
					  end;;

module IntOrder: ORDER with type t = int =
					  struct
					    type t = int
					    let compare s1 s2 = if s1<s2 then LESS else 
								  if s1>s2 then GREATER else EQUAL
					  end;;

module Dictionary (Key: ORDER): DICTIONARY with type key=Key.t =
struct
  type key = Key.t
  type 'a t = (key * 'a) list
  exception DuplicatedKey of key      (* error in insert *)
  let empty() = []
  let rec  insert dic (key1, el) =
    match dic with
      [] -> [(key1, el)]
    | ((k, e)::t) -> match Key.compare key1 k with
		       LESS-> (key1,el)::(k, e)::t
		     | EQUAL->raise(DuplicatedKey k) 
		     | GREATER -> (k,e)::(insert t (key1,el))

  let rec lookup dic key =
    match dic with
      [] -> None
    | ((k, e)::t) -> match Key.compare key k with
		       LESS-> None
		     | EQUAL-> Some e 
		     | GREATER ->  lookup t key

  let rec delete dic key =
      match dic with
      [] -> []
    | ((k, e)::t) -> match Key.compare key k with
		       LESS-> dic
		     | EQUAL-> t
		     | GREATER -> (k,e) :: delete t key

  let rec update dic (key,el) =
    match dic with
      [] -> [(key, el)]
    | ((k, e)::t) -> match Key.compare key k with
		       LESS-> (key, el) :: dic
		     | EQUAL->(key, el) :: t 
		     | GREATER -> (k, e) :: update t (key, el)

end;;

module SDict = Dictionary(StringOrder);;
module IDict = Dictionary(IntOrder);;

let ( <| ) d (key,value) = SDict.insert d (key,value);;

let dict = SDict.empty();;
let dict = dict <|("kot","trot")
<| ("slon","elephant")
<| ("pies","dog")
<| ("ptak","bird");;
SDict.lookup dict "pies";;
SDict.lookup dict "papuga";;
let dict = dict <| ("papuga","parrot");;
SDict.lookup dict "papuga";;


let ( <| ) d (key,value) = IDict.insert d (key,value);;

let dict = IDict.empty();;
let dict = dict <|(1,"trot")
<| (2,"elephant")
<| (3,"dog")
<| (4,"bird");;
IDict.lookup dict 3;;
IDict.lookup dict 5;;
let dict = dict <| (5 ,"parrot");;
IDict.lookup dict 5;;
