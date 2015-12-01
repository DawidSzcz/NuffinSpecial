type order = LESS | EQUAL | GREATER;;

module type ORDER = sig 
    type t 
    val compare : t-> t -> order 
    val print : t -> unit
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
				       	    let print s = print_int s; print_string " "
					  end;;

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
    val printPrefixTree: 'a t -> unit
  (* not necessary *)
  end;;

module Dictionary (Key: ORDER) : DICTIONARY with type key = Key.t = 
struct
type key = Key.t
type 'a t = Tip | Node of key * 'a * 'a t * 'a t
exception DuplicatedKey of key
let empty() = Tip
let rec lookup tree key =
  match tree with
    Node(k,info,t1,t2) ->(match Key.compare key k with
			    LESS -> lookup t1 key
			  | EQUAL   -> Some info
			  | GREATER -> lookup t2 key) 
  | Tip -> None

let rec insert tree (key, value) =
  match tree with
    Tip -> Node(key, value, Tip, Tip)
  | Node(k,info,t1,t2) -> 
     (match Key.compare key k with
	LESS -> Node(k, info, insert t1 (key,value), t2)
      | EQUAL   -> raise (DuplicatedKey key)
      | GREATER    -> Node(k, info, t1, insert t2 (key,value)))

let rec deletemin tree = 
  match tree with
    Node(k,info,Tip,t2) -> (k,info,t2)
  | Node(k,info,t1,t2) ->let (key,value,l) = deletemin t1
			 in (key,value,Node(k,info,l,t2))
  | Tip -> failwith "Dictionary: implementation error"

let rec delete tree key =
  match tree with
    Tip ->  Tip
  | Node(k,info,t1,t2) ->
     match Key.compare key k with
       LESS    -> Node(k,info, delete t1 key, t2) 
     | EQUAL   -> 
	( match (t1, t2) with 
	    (Tip, t2) -> t2
	  | (t1, Tip)  -> t1
	  | _  -> let (ki,inf,t_right) = deletemin t2 
		  in Node(ki,inf,t1,t_right))
     | GREATER -> Node(k,info, t1, delete t2 key)

let rec update tree (key, value) =
  match tree with
    Tip -> Node(key, value, Tip, Tip)
  | Node(k,info,t1,t2) ->
     ( match Key.compare key k with
	 LESS    -> Node(k, info, update t1(key,value), t2)
       | EQUAL   -> Node(k, value, t1, t2)
       | GREATER -> Node(k, info, t1, update t2(key,value)))

let rec printPrefixTree tree =
  match tree with
    Tip -> print_string "Leaf\n"
  | Node(k, info, t1, t2)  ->  Key.print k; print_string "\n"; printPrefixTree t1; printPrefixTree t2
end;;

module IDict = Dictionary(IntOrder);;

let rec makeTreeFromList list =
  match list with
    [] -> IDict.empty()
  | x::xs -> IDict.insert (makeTreeFromList xs) (x, "sth");;


let x = makeTreeFromList (List.rev [17; 10; 6; 14; 11; 26; 20; 34; 31; 37]);;

IDict.printPrefixTree x;;

IDict.printPrefixTree (IDict.insert x (18, "sth"));;
