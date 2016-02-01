bubsort(X,Y) :-
	append(Beg,[E1,E2|End],X),
	E1 > E2, !,
	append(Beg,[E2,E1|End],X2),
	bubsort(X2,Y).
bubsort(X,X).
