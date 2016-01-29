convert(List, Bag):-
	assertz(hash(null,null)), % powinienem wrzucic takiego x ktorego na pewno nie ma na liscie.
	makeSet(List),
	makeBag(Bag).
	
	
makeSet([]).
makeSet([H|T]):-
	hash(H, X),!,
	retract(hash(H,X)),
	X1 is X +1,
	asserta(hash(H,X1)),
	makeSet(T).
makeSet([H|T]):-
	asserta(hash(H, 1)),
	makeSet(T).


makeBag(Bag):-
	hash(X, Y),
	\+ Y = null, !,
	retract(hash(X,Y)),
	Bag = bag(X, Y, New),
	makeBag(New).
makeBag(void).
	
	
%convert(List, Bag):-
%	makeSet(List, void, Bag).
	
%makeSet([], A, A).
%makeSet([H|T], A, Bag):-
%	insert(H, A, Ret), !,
%	makeSet(T, Ret, Bag).
%makeSet([H|T], A, Bag):-
%	A1 = bag(H, 1, A),
%	makeSet(T, A1, Bag).		

%insert(X, bag(X, N, Rest), WskK):-!,
%	N1 is N + 1,
%	WskK = bag(X, N1, Rest).
	
%insert(X, bag(Y, N, Rest), WskK):-
%	WskK = bag(Y, N, New),
%	insert(X, Rest, New).
