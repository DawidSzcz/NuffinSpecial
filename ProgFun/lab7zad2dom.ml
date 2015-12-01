module CyclicQueue :
sig
  type 'a lnode = {item: 'a; mutable next: 'a lnode};
  
  exception Empty of string
  exception Full of string
  val create : int -> 'a t
  val enqueue: 'a * 'a t 
  val dequeue: 'a t -> unit      
  val first: 'a t -> 'a
  val isEmpty: 'a t -> bool
  val isFull: 'a t -> bool
end
struct
  let create n = let rec aux
  let enqueue: 'a * 'a t 
  let dequeue: 'a t -> unit      
  let first: 'a t -> 'a
  let isEmpty: 'a t -> bool
  let isFull: 'a t -> bool
end;;
