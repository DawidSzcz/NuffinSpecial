:- use_module(library(clpfd)).

wiezowce(N, W, K, Rows):-
	length(Rows, N),
	maplist(len(N), Rows),
	maplist(inss(1..N), Rows),
	transpose(Rows, Cols),
	maplist(all_different, Rows),
	maplist(all_different, Cols),
	Labels = [s,a,b,c,d,e,f,g,h],
	generate(Labels, 0,  N, [], Arc, Counter),
	tops(Rows, W, K, 1, N),
	rows(Rows, W, N, Arc, Counter),
	rows(Cols, K, N, Arc, Counter),
	maplist(labeling([ff, down]), Rows).
	
tops([], [], _, _, _).	
tops([H|T], [Hr|Tr], K, RowCount, N):-
	tops(H, Hr, K, RowCount, 1, N),
	R1 is RowCount + 1,
	tops(T, Tr, K, R1, N).

tops([H|T], (1,P), [_|Tc], RowNum, 1, N):-!,
	H #= N,
	tops(T, (1,P), Tc, RowNum, 2, N).
tops([H], (_, 1), _, _, N, N):-!,
	H #= N.
tops([H|T], (L,P), [(1, _)|Tc], 1, ColNum, N):-!,
	H #= N,
	NC is ColNum +1,
	tops(T, (L,P), Tc, 1, NC, N).
tops([H|T], (L,P), [(_,1)|Tc], N, ColNum, N):-
	H #= 5,
	NC is ColNum +1,
	tops(T, (L,P), Tc, N, NC, N).
tops([], _, [], _, _, _).
tops([H|T], (L, P), [(G,D)|Tc], RowNum, ColNum, N):-
	Max is min(min(N - L + ColNum, N - G + RowNum), min(2*N - ColNum - P + 1, min(2*N - RowNum - D +1, N))),
	H #=<Max,
	Nc is ColNum +1,
	tops(T, (L,P), Tc, RowNum, Nc, N).
	
generate([H|_], N, N, A, R, _):-
	!, genPrev(H, N, A, R).
generate([H|T], C, N, A, R, Counter):-
	C2 is C -1,
	genPrev(H, C2, A, A1),
	C1 is C +1,
	genNext(H, C1, N, T, A1, A2, Counter),
	generate(T, C1, N, A2, R, Counter).
	
genNext(_, C, N, _, A, A, _):-
 	C > N, !.
genNext(Label, C, N, [H|T], A, R, Counter):-
	functor(Term, arc, 4),
	arg(1, Term, Label),
	arg(2, Term, C),
	arg(3, Term, H),
	arg(4, Term, [Counter+1]),
	C1 is C +1,
	genNext(Label, C1, N, T, [Term|A], R, Counter).

genPrev(_, -1, _, []):-!.
genPrev(_, 0, A, A):-!.
genPrev(Label, N, A ,R):-
	functor(Term, arc, 3),
	arg(1, Term, Label),
	arg(2, Term, N),
	arg(3, Term, Label),
	N1 is N -1,
	genPrev(Label, N1, [Term|A], R).  

len(N, Row):-
	length(Row, N).
inss(X, Row):-
	Row ins X.
	
rows([], [], _, _, _).
rows([H|T], [(L,P)|Td], N, Arc, Count):-
	copy_term((Arc,Count),(Arc1,C1)).
	copy_term((Arc,Count),(Arc2,C2)).
	row(H, L, Arc1, C1),
	reverse(H, H1),
	row(H1, P, Arc2, C2),
	rows(T, Td, N, Arc, Count).

row(Vs, L, Arc, Counter) :-
   	Counter #=< L,
   	automaton(_, _, Vs,
		[source(s),sink(a),sink(b),sink(c), sink(d), sink(e), sink(f), sink(g)],
		Arc,
		[Counter], [0], [L]).

