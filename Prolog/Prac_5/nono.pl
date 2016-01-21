:- use_module(library(clpfd)).

nono(Rows, Cols, List):-
	length(Rows, M),
	length(Cols, N),
	length(List, M),
	maplist(len(N), List),
	maplist(ins_(0..1), List),
	maplist(narrow, List, Rows),
	transpose(List, ListCol),
	maplist(narrow, ListCol, Cols),
	maplist(labeling([down]), List).
	
	
narrow(L, Rep):-
	length(L, N),
	sum_list(Rep, O),
	sum(L, #=, O),
	findall(Tup, possibilities(Rep, N, Tup), TupList),
	tuples_in([L], TupList).

possibilities(Rep, N, List):-
	sum_list(Rep, O),
	N1 is N - O,
	maplist(putOnes, Rep, Ones),
	reverse(Ones, ROnes),
	putZeros(ROnes, N1, [], List).
	
putZeros([], N, A, List):-
	length(Zeros, N),
	maplist(zero, Zeros),
	append(Zeros, A, List), !.
putZeros([H], 0, A, List):-
	append(H, A, List).
putZeros([H|T], N, A, List):-
	N \= 0,
	N1 is N - 1,
	(putZeros([H|T],N1, [0|A], List);
		append(H, A, A1),
		putZeros(T, N1, [0|A1], List)). 
putOnes(X, Y):-
	length(Y, X),
	maplist(one, Y).
		
one(1).
zero(0).


ins_(X, L):-
	L ins X.
len(N, L):-
	length(L, N).

%countList(L, X):-
%	countList(L, 0, [], X).
%countList([], 0, A, A):-!.
%countList([], Count, A, [Count|A]).
%countList([0|T], 0, A, X):-
%	countList(T, 0, A, X), !.
%countList([0|T], Count, A, X):-
%	countList(T, [Count|A], X).
%countList([1|T], Count, A, X):-
%	C1 is Count+1,
%	countList(T, C1, A, X).
