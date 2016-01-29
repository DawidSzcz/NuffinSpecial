war(L1, L2, K):-
	asserta(first(L1)),
	asserta(second(L2)),
	openList(L1, Lo1-D1),
	openList(L2, Lo2-D2),
	open_append(Lo1-D1, [kot|Y]-Y, R),
	war(R, Lo2-D2, X-X, 0, K).
	
war(X-X, _, _, K, K):-
	var(X).
war(_, X-X, _, K, K):-
	var(X).
war([kot|[X]]-X, _, _, K, K).
war(_, [kot|[X]]-X, _, K, K).
war([kot|L1]-D1,L2-D2, B, S, K):-
	isInfinite(L1-D1, L2-D2, K);
		!,open_append(L1-D1, [kot|Y]-Y, R),
		war(R,L2-D2, B, S, K).
war([H1|T1]-D1,[H2|T2]-D2, BCards-D3, S, K):-
	S1 is S +1,
	(H1 > H2, !,
	open_append(BCards-D3, [H1,H2|DN]-DN, R),
	open_append(T1-D1, R, R1),
	war(R1, T2-D2, X-X, S1, K);
		(H1 < H2, !,
		open_append(BCards-D3, [H1,H2|DN]-DN, R),
		open_append(T2-D2, R, R2),
		war(T1-D1, R2, X-X, S1, K);
			S2 is S1 + 1,
			(battle(T1, T2, H1b-T1b, H2b-T2b), !,
			open_append(BCards-D3, [H1, H2, H1b, H2b|DN]-DN, R),
			war(T1b-D1, T2b-D2, R, S2, K);
				K = S1))).

battle([], _, _, _):-!, fail.
battle(_,[], _, _):-!, fail.
battle([kot,H1|T1], [H2|T2], H1-[kot|T1], H2-T2):-!.
battle([H1|T1], [H2|T2], H1-T1, H2-T2).

isInfinite(L1-D1, L2-D2, inf):-
	D1 = [], D2 = [],
	(first(L1),second(L2);
	asserta(first(L1)), asserta(second(L2)),
	fail).

openList([H], [H|D]-D):-!.
openList([H|T], [H|R]-D):-
	openList(T, R-D).
	
open_append(L1-L2, L2-D2, L1-D2).

