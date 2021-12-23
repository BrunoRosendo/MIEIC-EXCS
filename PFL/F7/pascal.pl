binom(K, K, 1) :- K > 0.
binom(_, 0, 1).
binom(N, K, 0) :- N < K, K > 0.
binom(N, K, Res) :-
    N > K,
    K > 0,
    N1 is N - 1,
    K1 is K - 1,
    binom(N1, K, B1),
    binom(N1, K1, B2),
    Res is B1 + B2.

pascalLine(N, Line) :- pascalLine(N, Line, 0, []).
pascalLine(N, Acc, K, Acc) :- K > N.
pascalLine(N, Line, K, Acc) :-
    K =< N,
    binom(N, K, B),
    append(Acc, [B], Acc1),
    K1 is K + 1,
    pascalLine( N, Line, K1, Acc1).

pascal(N, Lines) :- pascal(N, Lines, 0, []).
pascal(N, Acc, Counter, Acc) :- Counter > N.
pascal(N, Lines, Counter, Acc) :-
    N >= Counter,
    pascalLine(Counter, Line),
    Counter1 is Counter + 1,
    append(Acc, [Line], Acc1),
    pascal(N, Lines, Counter1, Acc1).
