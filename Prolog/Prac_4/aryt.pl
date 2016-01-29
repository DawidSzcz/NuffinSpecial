:- use_module(library(clpfd)).

aryt(Puzzle, Hash):-
	Puzzle=..[_,F, S],
	F=..[_,F1, F2],
	atom_chars(F1, C1),
	atom_chars(F2, C2),
	atom_chars(S, C3),
	makeHashMult(C1, [], Hash1, 0, S1),
	makeHashMult(C2, Hash1, Hash2, 0, S2),
	makeHashMult(C3, Hash2, Hash, 0, S3),
	doZero(C1, C2, C3, Hash),
	S3 #= S1 + S2,
	hashToTab(Hash, [], Tab),
	Tab ins 0..9,
	all_distinct(Tab),
	labeling([ff],Tab).
	
doZero([H1|_], [H2|_], [H3|_], Hash):-
	member((H1, X1), Hash),
	X1 #\= 0,
	member((H2, X2), Hash),
	X2 #\= 0,
	member((H3, X3), Hash),
	X3 #\= 0.

makeHashMult([],A,A,S, S).
makeHashMult([H|T], A, Hash, Acc, Sum):-
	length(T, L),
	(member((H, X), A),!,
	makeHashMult(T, A, Hash, Acc+X*10^L, Sum);
	makeHashMult(T, [(H,X)|A], Hash, Acc+X*10^L, Sum)).
	
hashToTab([], A, A).
hashToTab([(_,X)|T], A, R):-
	hashToTab(T, [X|A], R).
	
