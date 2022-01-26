impoe(X, L) :-
    length(Mid, X),
    append(L1, [ X | _ ], L),
    append(_, [ X | Mid ], L1).

langford(N, L) :-
    Len is N * 2,
    length(L, Len),
    langford_aux(N, L).

langford_aux(0, L) :- !.
langford_aux(N, L) :-
    impoe(N, L),
    N1 is N - 1,
    langford_aux(N1, L).
