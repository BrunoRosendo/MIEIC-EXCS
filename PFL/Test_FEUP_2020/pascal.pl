pascal(1, [1]).
pascal(N, L) :- 
    N > 1,
    N1 is N - 1,
    pascal(N1, PrevLine),
    pascal_sums(PrevLine, MidLine),
    append([1 | MidLine], [1], L).

pascal_sums(Line, Res) :- pascal_sums(Line, Res, []).

pascal_sums([], Res, Res) :- !.
pascal_sums([_], Res, Res) :- !.

pascal_sums([ Fst, Snd | T ], Res, Acc) :-
    Sum is Fst + Snd,
    append(Acc, [Sum], Acc1),
    pascal_sums([Snd | T], Res, Acc1).
