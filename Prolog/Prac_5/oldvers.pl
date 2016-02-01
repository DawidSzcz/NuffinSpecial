

wiezowce(N, W, K, R):-
	abolish(set/1),
	abolish(num/1),
	abolish(colsDesc/1),
	makeList(N, [], Set),
	asserta(set(Set)),
	asserta(num(N)),
	length(Rows, N),
	maplist(len(N), Rows),
	transpose(Rows, Columns),
	asserta(colsDesc(K)),
	fillPos(N, W, K, Pos),
	fillBoard(N, Rows, Columns, W, Pos),
	checkColumns(Columns, K),
	transpose(Columns, R).

fillPos(N, W, K, Pos):-
	length(Pos, N),
	maplist(len(N), Pos),
	fillPos(W, K, N, 1, Pos).
	
fillPos([],_, _, _ ,[]).
fillPos([H|T], Kol, N, RowNum, [Row|Rows]):-
	posRow(H, Kol, RowNum, 1, N, Row),
	NR is RowNum+1,
	fillPos(T, Kol, N, NR, Rows).

posRow((1, P), [_|T], RowNum, 1, N, [0|Row]):-!,
	posRow((1, P), T, RowNum, 2, N, Row).
posRow((_, 1), _, _, N, N, [0]):-!.
posRow((L, P), [(1,_)|T], 1, ColNum, N, [0|Row]):-!,
	NC is ColNum +1,
	posRow((L, P), T, 1, NC, N, Row).
posRow((L, P), [(_,1)|T], N, ColNum, N, [0|Row]):-!,
	NC is ColNum +1,
	posRow((L, P), T, N, NC, N, Row).	
posRow(_, [], _, _, _, []).	
posRow((L,P), [(G,D)|T], RowNum, ColNum, N, [Field|Row]):-
	Temp1 = min(N - L + ColNum, N - G + RowNum),
	Temp2 = min(2*N - ColNum - P + 1, 2*N - RowNum - D +1),
	Temp3 = min(Temp1, N),
	Field is min(Temp2, Temp3),
	NC is ColNum +1,
	posRow((L,P), T, RowNum, NC, N, Row). 
	  
	

transpose([T], X):-
	makeL(T, X).
transpose([H|T], Y):-
	transpose(T, X),
	transpose(H, X, Y).
	
transpose([],[], []).
transpose([H|T], [H1|T1], [[H|H1]|R]):-
	transpose(T, T1, R).
	
makeL([], []).
makeL([H|T], [[H]|T1]):-
	makeL(T, T1).
		
len(N, Row):-
	length(Row, N).
	
fillBoard(0, [], _, [], []):-!.
fillBoard(N, [H|T], Columns, [HD|TD], [HPos|TPos]):-	
	fillRow(H, Columns, HD, HPos),
	N1 is N -1,
	fillBoard(N1, T, Columns, TD, TPos).

fillRow(Row, Cols, (L,P), Pos):-
	num(N),
	set(Set),	
	colsDesc(Desc),
	fRow(Set, Row, Cols, Desc, L, N, 0, Pos),
	reverse(Row, RRow),
	check(RRow, 0, 0, P).
	
fRow([], [], [], [], 0, _, _, []):-!.
fRow(_, _, _, _, -1, _, _, _):-!, false.
fRow(Set, [H|T], [Hc|Tc], [(G,_)|Tdesc], L, N, Max, [0|TPos]):-!,
	select(N, Set, NSet),
	mem(Hc, N, G, N, 0),
	H = N,
	makeControls(L, Max, H, NMax, NL),
	N >= NMax + NL,
	fRow(NSet, T, Tc, Tdesc, NL, N, NMax, TPos);
	fail.
fRow(Set, [H|T], [Hc|Tc], [(G,_)|Tdesc], L, N, Max, [HPos|TPos]):-
	select(R, Set, NSet),
	R =< HPos,
	mem(Hc, R, G, N, 0),
	H = R,
	makeControls(L, Max, H, NMax, NL),
	N >= NMax + NL,
	fRow(NSet, T, Tc, Tdesc, NL, N, NMax, TPos);
	fail.

mem([], _, 0, _, _).
mem([H|_], _, _, _, _):-
	var(H), !.
mem([H|T], X, G, N, Max):-
	H \= X,
	makeControls(G, Max, H, NMax, NG),
	N >= NMax + NG,
	mem(T, X, NG, N, NMax).
	
makeControls(L, Max, H, NMax, NL):-
	H > Max,!,
	NMax = H,
	NL is L -1;
	NMax = Max,
	NL = L.
	

checkColumns([], []).
checkColumns([H|T], [(_,D)|Td]):-
	reverse(H, H1),
	check(H1, 0, 0, D),
	checkColumns(T, Td).

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

	
