dict(3, trzy,dict(1, jeden,dict(0, zero, N,N),dict(2, dwa, N, N)),dict(4, cztery, N, dict(5, piec, N, N))).

lookup(_, Dict, _):-
	var(Dict), !, false.
lookup(Key, dict(Key,Value,_,_), Value):- !.
lookup(Key, dict(K,V,_,R), Value):-
	Key > K,!,
	lookup(Key, R, Value).
lookup(Key, dict(_,_,L,_), Value):-
	lookup(Key, L, Value),!.
