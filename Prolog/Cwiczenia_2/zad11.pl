assertp(X):-
	assertz(X).
	
assertn(X):-
	asserta((X:-!,false)).
