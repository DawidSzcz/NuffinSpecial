:- use_module(library(clpfd)).


:- op(400, yfx, or).
:- op(300, yfx, and).
:- op(200, fy, not).


sat(X):-
	satisfiable(X, Y),
	Y is 1, !.
	
satisfiable(X, X):-
	number(X),!.
satisfiable(X, X):-
	var(X),
	X is 1.
satisfiable(X, X):-
	var(X),!,
	X is 0.
satisfiable(X, R):-
	X=..[not,T],
	satisfiable(T, T1),
	not(T1, R).
satisfiable(X, R):-
	X=..[O,F,S],
	satisfiable(F, F1),
	satisfiable(S, S1),
	functor(Op, O, 3),
	arg(1, Op, F1),
	arg(2, Op, S1),
	arg(3, Op, R),
	Op.

not(1, X) :- X is 0.
not(0, X) :- X is 1.

or(1, _, R) :- R is 1,!.
or(_, 1, R) :- R is 1, !.
or(_, _, R) :- R is 0.

and(1, 1, 1):-!.
and(_, _, 0).
