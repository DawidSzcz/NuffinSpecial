inference(Facts, Rules, MaxLength, Ret):-
	op(1000, xfx, >>),
	asserta(rules(Rules)),
	infer(Facts, Rules, MaxLength, Ret).
	
infer(Facts, [], _, Facts).
infer(Facts, [H|T], MaxL, Ret):-
	copy_term(H, Pred>> Cons),
	findall(Cons, match(Pred, Facts, Facts), List),
	flatten(List, FlattenList),
	distinctElements(FlattenList, Facts, MaxL, NewFacts),
	(NewFacts = Facts,
		infer(Facts, T, MaxL, Ret);
		rules(AllRules),
		infer(NewFacts, AllRules, MaxL, Ret)).
infer(Facts, [_|T], MaxL, Ret):-
	infer(Facts, T, MaxL, Ret).

match([], _, _).
match([H|T], [H1|_], All):-
	H = H1,
	match(T, All, All).
match(Pred, [_|T1], All):-
	Pred \= [],
	match(Pred, T1, All).

distinctElements([], A, _,A).
distinctElements([H|T], A, MaxL, Ret):-
	\+member(H, A),
	checkDepth(H, Depth),
	Depth =< MaxL,	
	distinctElements(T, [H|A],MaxL, Ret); % bez powtorzen w nastepniku	
	distinctElements(T, A, MaxL, Ret).
	
	
checkDepth(X, 1):-
	atom(X); var(X).
checkDepth(Term, Depth):-
	Term=..[_|T],
	checkListDepth(T, 0, D1),
	Depth is D1 + 1.
	
checkListDepth([], A, A).
checkListDepth([H|T], A, Depth):-
	checkDepth(H, NewDepth),
	Max = max(A, NewDepth),
	checkListDepth(T, Max, Depth).
	
	
