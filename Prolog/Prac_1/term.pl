term(Sign, Size, Term):-
	var(Size),!,
	parse(Sign, List),
	unify(List, Term, 0, Size).
term(Sign, Size, Term):-
	parse(Sign, List),
	try(List, Size, Term, List).
	
unifyList(_,[],A,A).
unifyList(List, [H|T], A, Size):-
	unify(List, H, 0, Ret),
	A1 is A + Ret,
	unifyList(List, T, A1, Size). 
	
unify(_, Term, A, Size):-
	functor(Term, _, 0),!,
	Size = A + 1.
unify(List, Term, A, Size):-
	contains(List, Term),
	Term=..[_|T],
	A1 is A + 1,
	unifyList(List, T, A1, Size).
	
contains([H|_], Term):-
	\+ \+ H = Term, !.
contains([_|T], Term):-
	contains(T, Term).
	
parse([],[]).
parse([H|T], L):-
	H=..[_,F,A],
	functor(Term, F, A),
	parse(T, L1),
	L = [Term|L1].
	
try([H|_], Size, Term, All):-
	functor(H, _, Arr),% Okazuje sie ze to sa caly czas te same wskazniki - lol.
	uni(H, All, Arr, Size, 1, RSize,All),
	Size is RSize,
	Term = H.
try([_|T], Size, Term, All):-
	try(T,Size,Term, All).
	
uni(_,_,0,_,RSize,RSize,_):-!.
uni(_,_,_,Size,RSize,_,_):-
	number(Size), 
	RSize >= Size, !,
	false.
uni(Term, [H|_], Curr, Size, A, RSize, All):-
	functor(H, _, Arr),
	arg(Curr, Term, H),
	A1 is A + 1,
	uni(H, All, Arr, Size, A1, RS, All),
	C1 is Curr -1,
	uni(Term, All, C1, Size, RS, RSize,All).
uni(Term, [_|T], Curr, Size, A, RSize, All):-
	uni(Term, T, Curr, Size, A, RSize, All).
	

