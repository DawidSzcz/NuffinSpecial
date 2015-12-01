(*Dawid Szczyrk*)

(*2*)
let isspace ch = (ch =' ') || (ch ='\t') || (ch ='\n') || (ch = '\r') ;;

let parse_number line =
	let i = ref 0
	and flt = ref false 
	and dec = ref 0.1
	and number = ref 0.0 in
		while  !i < (String.length line)&& not(isspace (line.[!i])) do
			if	(line.[!i]) == '.' then 
				flt := true
			else if !flt then begin
					number := !number +. float_of_int(int_of_char(line.[!i]) - 48) *. !dec;
					dec := !dec/.10.0;
				end
				else
					number := !number*.10.0 +. float_of_int(int_of_char(line.[!i])) -. 48.0;
			i := !i +1;
		done;
	number;;

let write_array output arr = 
	let ofile = open_out output in
		let rec aux arr =
			match arr with
			  [] -> ();
			| x::xs -> output_string ofile (string_of_float !x); aux xs
		in aux arr;;

let sortuj_plik input output =
  	let ifile  = open_in input in
		let n = ref (int_of_string(input_line ifile)) 
		and arr = ref [] in 
			while !n > 0 do 
				arr:= parse_number (input_line ifile) :: !arr;
				n := !n-1;
			done;
			write_array output (List.sort compare !arr);;

sortuj_plik "input" "ouutput";;
