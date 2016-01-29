sum_list(L, N):-
	sum_list(L, N, 0).
	
sum_list([], A, A).
sum_list([H|T], N, A):-
	A1 is A + H,
	sum_list(T, N, A1).
