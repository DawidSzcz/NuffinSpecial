occurences(S,Term,N):-
	occurences(S, Term, 0, N).

occurences(_, [], A, N):-!,
	N is A.
occurences(S, [S|T], A, N):-!,
	A1 is A +1,
	occurences(S, T, A1, N).
occurences(S, [H|T], A, N):-
	atom(H); number(H), !,
	occurences(S, T, A, N).
occurences(S,[H|T], A, N):-
	occurences(S, H, 0, N1),
	A1 is A + N1,
	occurences(S, T, A1, N).
occurences(S, Term, A, N):-
	Term =.. [_|T],
	occurences(S, T, A, N).
