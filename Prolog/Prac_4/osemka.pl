osemka(S1, S2, N):-
	localize(S1, P),
	empty_heap(Heap),
	asserta(visited(S1)),
	resolve((S1, P, 0), S2, N, Heap),
	abolish(visited/1).
	
resolve((S, _, N), S, N, _).
resolve(State, S2, N, Heap):-
	makeStates(State, NewStates),
	add(NewStates, S2, Heap, TempH),
	get_from_heap(TempH, _, State1, NH),
	resolve(State1, S2, N, NH).
	
makeStates((Curr, P, N), R):-
	N1 is N + 1,
	findall((New, P1, N1),(newState(Curr, P, New, P1),\+visited(New), asserta(visited(New))),
	R).
	
add([], _, H, H).
add([(State, Poz, N)|T], S, Heap, NH):-
	prioritize(State, S, 0, Pr),
	Pr1 is N + Pr,
	add_to_heap(Heap, Pr1, (State, Poz, N), TempH),
	add(T, S, TempH, NH). 
	
newState(Curr, P, New, P1):-
	P mod 3 =\= 0,
	P1 is P + 1,
	swap(Curr, P, 1, New).
newState(Curr, P, New, P1):-
	P < 7,
	P1 is P + 3,
	swap(Curr, P, 3, New).
newState(Curr, P, New, P1):-
	P mod 3 =\= 1,
	P1 is P - 1,
	swap(Curr, P1, 1, New).
newState(Curr, P, New, P1):-
	P > 3,
	P1 is P - 3,
	swap(Curr, P1, 3, New).

prioritize([], [], A, A).
prioritize([H|T1], [H|T2], A, N):-!,	
	prioritize(T1, T2, A, N).
prioritize([_|T1], [_|T2], A, N):-
	A1 is A +1,
	prioritize(T1, T2, A1, N).

localize([o|_], 1):-!.
localize([_|T], N1):-
	localize(T, N),
	N1 is N +1.
	
	
swap([H1, H2, H3, H4|T], 1, 3, [H4, H2, H3, H1|T]).
swap([H1, H2|T], 1, 1, [H2, H1|T]). 
swap([H|T], Y, Odl, [H|R]):-
	Y1 is Y - 1,
	swap(T, Y1, Odl, R).
