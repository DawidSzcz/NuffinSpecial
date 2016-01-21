:- use_module(library(clpfd)).

queens(L,Board):-
	length(Board, L),
	Board ins 1..L,
	all_distinct(Board),
	fractals(Board),
	labeling([ff],Board).
	
fractals([]).
fractals([H|T]):-
	fractals(H, 1, T),
	fractals(T).
fractals(_, _, []).
fractals(Row, Col, [NR|T]):-	
	Row#\=NR - Col,
	Row#\=NR + Col,
	NC is Col +1, 
	fractals(Row, NC, T).
	

