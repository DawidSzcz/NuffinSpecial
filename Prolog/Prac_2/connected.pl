
connected(X,Y):-
	connected(X,Y,[]).

connected(X, Y, _):-
	edge(X, Y), !.
	
connected(X, Y, O) :-
	edge(X, Z),
	\+ member(Z, O),
	connected(Z,Y, [X|O]).
