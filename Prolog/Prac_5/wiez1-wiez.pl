:- use_module(library(clpfd)).

wiezowce(N, W, K, Rows):-
	length(Rows, N),
	length(VLeft, N),
	length(VRight, N),
	length(VUp, N),
	length(VDown, N),
	maplist(len(N), VLeft),
	maplist(len(N), VRight),
	maplist(len(N), VUp),
	maplist(len(N), VDown),
	maplist(len(N), Rows),
	transpose(Rows, Columns),
	maplist(inss(0..1), VLeft),
	maplist(inss(0..1), VRight),
	maplist(inss(0..1), VUp),
	maplist(inss(0..1), VDown),
	maplist(inss(1..N), Rows),
	maplist(all_different, Columns),
	maplist(all_different, Rows),
	borders(Rows, W, N),
	borders(Columns, K, N),
	sumRows(VLeft, VRight, W),
	sumRows(VUp, VDown, K),
	visible(VLeft, VRight, Rows),
	visible(VUp, VDown, Columns),
	tops(Rows, W, N),
	tops(Columns, K, N),
	flatten(Rows, R1),
	labeling([ff, down],R1).
	
tops([], [], _).	
tops([H|T], [(L,P)|T1], N):-
	tops(H, L, P, N, 1),
	tops(T, T1, N).

tops([], _, _, _, _).
tops([H|_], L, _, N, Count):-
	L > Count,
	H #=< N + Count - L.
tops([H|_], _, P, N, Count):-
	Count + P - 1 > N, 
	H #=< 2* N - Count - P +1.
tops([_|T], L, P, N, C):-
	C1 is C+1,
	tops(T, L, P, N, C1).
	
sumRows([], [], []).
sumRows([H1|T1], [H2|T2], [(L,P)|T3]):-
	sum(H1, #=, L),
	sum(H2, #=, P),
	sumRows(T1, T2, T3).
	
visible([], [], []).
visible([H|T], [H1|T1], [H2|T2]):-
	visibleLeft(H, H2),
	visibleRight(H1, H2, _),
	visible(T, T1, T2).
	
visibleRight([H], [H1], [H1]):-
	H #=1.
visibleRight([H|T], [H1|T1], [H1|R]):-
	visibleRight(T, T1, R),
	makeExp(H1, R, 1, Exp),
	H #<==> Exp.

visibleLeft([H1|T1], [H2|T2]):- 
	H1 #= 1,
	visibleLeft(T1, T2, [H2]). 
visibleLeft([], [], _).
visibleLeft([H1|T1], [H2|T2], List):-
	makeExp(H2, List, 1, Exp),
	H1 #= 1 #<==> Exp,
	visibleLeft(T1, T2, [H2|List]).
	
makeExp(_, [], A, A).
makeExp(H2, [H|T], A, Exp ):-
	makeExp(H2, T, A #/\ (H2 #> H), Exp).
	

borders([], [], _).
borders([[H|_]|_], [(1, _)|_], N):-
	H #= N.
borders([H|_], [(_, 1)|_], N):-
	setLast(H, N).
borders([[H|T]|T1], [(L,P)|T2], N):-
	H #=< (N - L +1),
	constrainLast(T, N, P),
	borders(T1, T2, N).
	
setLast([T], N):-
	!,T #= N.
setLast([_|T], N):-
	setLast(T, N).
	
constrainLast([T], N, X):-
	!,T #=< N - X +1.
constrainLast([_|T], N, X):-
	constrainLast(T, N, X).
		
len(N, Row):-
	length(Row, N).
	
inss( X, Y) :- Y ins X.
	

checkColumns([], []).
checkColumns([H|T], [Hd|Td]):-
	check(H, Hd),
	checkColumns(T, Td).

check(List, (L, P)):-
	check(List, 0, 0, L),
	reverse(List, L1),
	check(L1, 0, 0, P).

check([], _, L, L).
check([H|T], Max, A, L):-
	H > Max,!,
	A1 is A + 1,
	check(T, H, A1, L);
	check(T, Max, A, L).


makeList(0, A, A):- !.
makeList(N, A, List):-
	N1 is N -1,
	makeList(N1, [N|A], List).
