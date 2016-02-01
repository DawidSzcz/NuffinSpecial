(*Dawid Szczyrk*)

(*4*)
let powers (z,y) =
	let rec p_aux (z, x, y) =
		if y < 0 then
			failwith("I saw what you did there")
		else if y = 0 then
				[z]
			else
				if x = 0 then
					0::p_aux(z*x,x, y-1)
				else
					z::p_aux(z*x,x, y-1)
	in p_aux(1,z,y);;

powers(2,3);;
powers(5,5);;
powers(0,1);;
powers(-1,4);;

(*5*)
let split (tab, pivot) =
	let rec split_aux tab pivot fst snd =
		if tab = [] then
			(List.rev fst, List.rev snd)
		else if( List.hd(tab) <= pivot) then
				split_aux (List.tl(tab)) pivot (List.hd(tab)::fst) snd
			else
				split_aux (List.tl(tab)) pivot fst (List.hd(tab)::snd)
	in split_aux tab pivot [] [];;

split ([1;3;2], 2);;
split ([1;4;3;2;6;8;1], 4);;
split ([1;2;3;4;5], 7);;
split ([4;5;6;7], 3);;

(*6*)
let segment (tab, n) =
	let rec s_aux (tab, n, curr) = 
		if tab = [] then
			[[]]
		else
			if curr = n then
				[]::(s_aux (tab, n, 0))
			else
				let x = s_aux ((List.tl(tab)), n, curr+1) in
					(List.hd(tab)::List.hd(x))::List.tl(x)
	in s_aux (tab, n, 0);;

segment ([1;2;3;4;5;6;7;8;9], 2);;
segment ([1;2;3;4;5;6;7;8;9], 1);;
segment ([1;2;3;4;5;6;7;8;9], 6);;

(*7*)

let swap (tab, pivot) =
	let rec s_aux tab pivot =
		if tab = [] then
			([],[])
		else
			if pivot <= 0 then
				([], tab)
			else
				let x = s_aux (List.tl(tab)) (pivot -1) in
					(List.hd(tab)::fst(x), snd(x))
	in let x = s_aux tab pivot in
		List.append (snd(x)) (fst(x));;



swap ([1;2;3;4;5;6;7], 2);;
swap ([1;2;3;4;5;6;7], 5);;
swap ([1;2;3;4;5;6;7], (-1));;
swap ([1;2;3;4;5;6;7], 8);;















