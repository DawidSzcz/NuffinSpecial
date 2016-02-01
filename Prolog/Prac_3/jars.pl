jars(V, T, K):-
	maplist(makeJar, V, Jars),
	explore([Jars], [], [Jars], T, 0, K).
	
makeJar(X, (X, 0)). 

explore([], [], _, _, _, _):-!,
	false.
explore([], NextStep, AllStates, T, K, Ret):-
	K1 is K +1,
	explore(NextStep, [], AllStates, T, K1, Ret).
explore([H|_], _, _, Am, K, K):-
	member((_,Am), H).
explore([H|T], NextStep, States, Am, K, Return):-
	fillAll(H, States, All, Q1),
	emptyAll(H, All, All2, Q2),
	pourAll(H, All2, All3, Q3),
	append(Q1, Q2, T1),
	append(T1, Q3, T2),
	append(NextStep, T2, NS1),
	explore(T,NS1, All3, Am, K, Return).
	 
fillAll(State, States, AllStates, NewStates):-
	findall(FillState, fill(State, States, FillState), NewStates),
	append(NewStates, States, AllStates).
	
fill(State, States, FillState):-
	append(Pref, [(X,_)|T], State),
	append(Pref, [(X, X)|T], FillState),
	\+ member(FillState, States).

emptyAll(State, States, AllStates, NewStates):-
	findall(EmptyState, empty(State, States, EmptyState), NewStates),
	append(NewStates, States, AllStates).
empty(State, OldStates, EmptyState):-
	append(Pref, [(X,_)|T], State),
	append(Pref, [(X, 0)|T], EmptyState),
	\+ member(EmptyState, OldStates).

pourAll(State, States, AllStates, NewStates):-
	findall(PourState, pour(State, States, PourState), NewStates),
	append(NewStates, States, AllStates).

pour(State, States, PourState):-
	append(Prefix, [F|T], State),
	append(Infix, [S|T2], T),
	(pour(F, S, Fr, Sr),
	append(Prefix, [Fr|Infix], Temp),
	append(Temp, [Sr|T2], PourState),
	\+member(PourState, States);
	pour(S, F, Sr, Fr),
	append(Prefix, [Fr|Infix], Temp),
	append(Temp, [Sr|T2], PourState),
	\+member(PourState, States)).

pour((J1, F1), (J2, F2), (J1, F1r), (J2, F2r)):-
	F1 < J2 - F2, !,
	F2r is F1 + F2,
	F1r is 0;
	F1r is F1 - (J2 - F2),
	F2r is J2.
