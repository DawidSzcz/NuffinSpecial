edge(a, b).
edge(b, c).
edge(c, d).
edge(b, e).


connected(X,Y):-
	connected(Y, [X], []).

connected(Y, [Y|_], _):-!.
connected(Y, [H|T], O):-
	write(H), write('\n'),
	findall(X, (edge(H, X), \+member(X, O)), NextStep),
	append(T, NextStep, Queue),
	connected(Y, Queue, [H|O]).
