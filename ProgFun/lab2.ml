(*Dawid Szczyrk*)

(*1*)
let rec fib x = 
	if x = 0 
		then 0 
	else if x = 1 
			then 1 
	 	else 
			fib(x-1) + fib(x-2);;

let fib_rec x =
	let rec f_aux x f s =
		if x = 0 then f
		else f_aux (x-1) s (f+s)
	in f_aux x 0 1 ;;

fib_rec 40;;
fib 40;;

(*2*)
let (<->) pt1 pt2 = 
	match (pt1, pt2) with
		((x1,y1,z1), (x2,y2,z2) ) 	-> sqrt((x1-.x2)**2.+.(y1-.y2)**2.+.(z1-.z2)**2.)
		|_				-> failwith("wrong arguments");;

(1.,1.,1.) <-> (1.,1.,0.);;
(1.,2.,3.) <-> (4.,5.,6.);;

(*3*)
let rec (<--) tab el =
	match tab with
		[] 			-> [el]
		|h::t when el <= h 	-> el :: h :: t
		|h::t 			-> h :: ((<--) t el);; 

[1;2;5;6] <-- 3;;
[1;2;5;6] <-- (-1);;
[1;2;5;6] <-- 3;;
[1;2;5;6] <-- 5;;
[1;2;5;6] <-- 8;;

(*4*)
let rec take len tab =
	match (len, tab) with
		(x, _)	when x <=0	-> []
		|(_, [])		-> []
		|(x, h::t)		-> h :: take (x-1) t;;

take 2 [1;2;3;4;5;6];;
take (-2) [1;2;3;4;5;6];;
take 8 [1;2;3;4;5;6];;

(*5*)
let rec drop len tab =
	match (len, tab) with
		(x, _)	when x <=0	-> tab
		|(_, [])		-> []
		|(x, h::t)		-> drop (x-1) t;;

drop 2 [1;2;3;4;5;6];;
drop (-2) [1;2;3;4;5;6];;
drop 8 [1;2;3;4;5;6];;





