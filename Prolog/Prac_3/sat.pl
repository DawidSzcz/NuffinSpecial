:- op(400, yfx, or).
:- op(300, yfx, and).
:- op(200, fy, neg).


sat(X):-
	satisfiable(X, 1).
	
satisfiable(X, X):-
	number(X).
satisfiable(X, X):-
	var(X), !,
	(X is 1; X is 0).
satisfiable(X, R):-
	X=..[neg,T],
	satisfiable(T, T1),
	R is -T1 +1.
satisfiable(X, R):-
	X=..[or,F,S],
	satisfiable(F, F1),
	satisfiable(S, S1),
	or(F1, S1, R).
satisfiable(X, R):-
	X=..[and,F,S],
	satisfiable(F, F1),
	satisfiable(S, S1),
	and(F1, S1, R).

or(0, 0, 0) :-!.
or(_, _, 1).

and(1, 1, 1):-!.
and(_, _, 0).
