convert(List, Bag):-
	makeSet(List, void, Bag).
	
makeSet([], A, A).
makeSet([H|T], A, Bag):-
	insert(H, A, Ret), !,
	makeSet(T, Ret, Bag).
makeSet([H|T], A, Bag):-
	A1 = bag(H, 1, A),
	makeSet(T, A1, Bag).
	

insert(X, bag(X, N, Rest), Ret):-!,
	N1 is N + 1,
	Ret = bag(X, N1, Rest).
	
insert(X, bag(Y, N, Rest), Ret):-
	insert(X, Rest, New),
	Ret = bag(Y, N, New).
	
