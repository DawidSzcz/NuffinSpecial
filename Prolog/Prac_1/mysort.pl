divide(X, [], [], X).
divide(X, [_], [], X).
divide([H|T1], [_,_|T2], P, S):-
	P = [H|P1],
	divide(T1, T2, P1, S).

merge([H1], [H2], Z):-
	H1>H2, Z = [H2,H1];
	Z = [H1, H2].
merge([H], [H2|T2], Z):-
	H>H2, Z = [H2|Z1], merge([H], T2, Z1);
	Z = [H,H2|T2].
merge([H1|T1], [H], Z):-
	H>H1, Z = [H1|Z1], merge(T1, [H], Z1);
	Z = [H,H1|T1].
merge([H1|T1], [H2|T2], Z):-
	H1>H2, Z = [H2|Z1], merge([H1|T1], T2, Z1);
	Z = [H1|Z1], merge(T1, [H2|T2], Z1).
	

mysort([H], [H]):-!.
mysort(L, Z):-
	divide(L, L, P, S),
	mysort(P, Z1),
	mysort(S, Z2),
	merge(Z1, Z2, Z).
	
