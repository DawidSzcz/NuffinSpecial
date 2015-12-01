module Queue = 
  struct
    type 'a t = EmptyQueue | Enqueue of 'a * 'a t
    exception Empty of string 
    let create() = EmptyQueue
    let enqueue(e, q) = Enqueue(e, q)
    let dequeue =  function x -> 
			    let rec aux = function
				Enqueue(_, EmptyQueue) -> EmptyQueue
			      | Enqueue(e, q) -> Enqueue(e, aux q)
			      | EmptyQueue -> EmptyQueue
			    in aux x
    let first = function x ->
			 let rec aux = function
			     Enqueue(e, EmptyQueue) -> e
			   | Enqueue(_, q) -> aux q
			   | EmptyQueue -> raise(Empty "I see what you did there")
			 in aux x  
    let isEmpty = function EmptyQueue -> true   | Enqueue _ -> false
  end;;


module QueueList = 
  struct
    type 'a t = { mutable l : 'a list }
    exception Empty of string 
    let create() = { l = [] }
    let enqueue(e, q) = q.l <- e:: q.l
    let dequeue q = q.l <-
		      let rec aux = function
			  [] -> []
			| [e] -> []
			| (e::r) -> e::(aux r)
		      in aux q.l
    let first q = let rec aux = function
		      [] -> raise(Empty "I see what you did there")
		    | [e] -> e
		    | (e::r) -> aux r
		  in aux q.l
    let isEmpty q = q.l = []
  end;;

module QueueList = 
  struct
    type 'a t = { mutable f : 'a list; mutable s : 'a list }
    exception Empty of string 
    let create() = { f = []; s = [] }
    let enqueue(e, q) = if q.f = [] then
			  q.f <- [e]
			else
			  q.s <- e :: q.s
    let dequeue q = 
      match q.f with
	[] -> []
      | [e] -> q.f <- List.rev q.s; e
      | x::xs -> x
    let first q = let rec aux = function
		      [] -> raise(Empty "I see what you did there")
		    | x::xs -> x
		  in aux q.f
    let isEmpty q = q.f = []
  end;;

let x = QueueList.create();;



