wygrywa(L, K):-
	max(L, 0, M),
	fill(M, [p], L2),
	K1 is K - M  - 1,
	wygrywa(L, L2, K1).

wygrywa(_, [H|_], -1):-!,
	H == w.
wygrywa(L, L2, K):-
	K1 is K-1,
	(
		wyg(L, 1, L2), !,
		wygrywa(L, [w|L2], K1);
		wygrywa(L, [p|L2], K1)
	).
	
wyg([], _, _):-false.
wyg([Nr|_], Nr, [p|_]):-!.
wyg([Nr|T], Nr, [w|T1]):-!,
	Nr1 is Nr + 1,
	wyg(T, Nr1, T1).
wyg([H|T], Nr, [_|T1]):-
	Nr1 is Nr + 1,
	wyg([H|T], Nr1, T1).

fill(0, A, A):-!.
fill(M, A, R):-
	M1 is M-1, 
	fill(M1, [w|A], R).
	
max([], A, A).
max([H|T], A, R):-
	H > A, !,
	max(T, H, R).
