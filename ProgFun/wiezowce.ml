module type SET_SIG =
sig
    type set = {mutable set : int list; mutable curr : int}
    exception Empty of string 
    val create: int -> set
    val next: set -> unit
    val take: set -> unit
    val print: set -> unit
end;;

module Set : SET_SIG= 
  struct
    type set = {mutable set : int list; mutable curr : int}
    exception Empty of string 
    
    let create n =  
      let rec makeSet a i n = 
	if i = n then
	  a
	else
	  makeSet (i::a) (i+1) n
      in {curr = n; set = makeSet [] 1 n }



    let next s = let rec takeNext a rest c =
		  match rest with
		    h::t when c < h -> takeNext (h::a) t c
		  | h::t when c > h -> s.set <- List.rev_append (c::a) t; s.curr <- h
		  | [] -> raise(Empty "")
		in takeNext [] s.set s.curr;;

    let take s=
      match s.set with
	h::t -> s.curr<-h; s.set <- t
      | _ -> raise(Empty "");;

    let empty set = 
      if set.set = [] then
	true 
      else
	false;;

    let print set =
      print_string (String.concat "curr: " [string_of_int set.curr; " set: "]);
      List.iter (Printf.printf "%d ") set.set;
      print_string "\n";;
  end;;


let rec check left arr n high =
  match arr with
    h::t when h > high -> check left t (n+1) h
  | h::t when h < high -> check left t n high
  | [] when left = n -> ()
  | _ -> raise (Empty "");;



let rec fillRow l r set a =
  if Set.empty set then
    check l r a 0 0;
    a
  else
    try
      Set.take set;
      fillRow l r set set 
    with 
      Failure -> Set.next set;
      fillRow ((Set.take set)::a);;





(*let x = Set.create 5;;
Set.next x;;
Set.next x;;
Set.next x;;
Set.print x;;
Set.take x;;
Set.next x;;
Set.print x;
 *)

(*let rec wiezowce n w k a =
  match w with
    [] -> List.rev a
  | h :: t -> wiezowce n t k ((fillRow h [] n (\n -> makeSet []) :: a) 

let rec fillRow (L, R) a n =
  match n with
    0 -> a
  | _ ->;;



let x = makeSet [] 10;;

let rec takeOne set =
  match set with
    [] -> raise ( Failure "" )
  | (h :: t) -> try is6 h
		with Failure -> h: takeOne t
  try is6 x 

let is6 x =
  if x = 6 then
    ()
  else
    raise (Failure "");;




let rec generate n a x =
  match n with
    0 -> List.rev a
  | _ -> generate (n-1) (x :: a) x;;
			 

let x = wiezowce 4 3 3;;*)
