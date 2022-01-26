:-use_module(library(lists)).
:-use_module(library(between)).

double(X, Y):- Y is X*2.
sum(A, B, S):- S is A+B.
even(X):- 0 =:= X mod 2.

map(Pred, List1, List2) :- map(Pred, List1, List2, []).
map(_, [], List2, List2).
map(Pred, [H | T], List2, Acc) :-
    Func =.. [Pred, H, Res],
    Func,
    append(Acc, [Res], Acc1),
    map(Pred, T, List2, Acc1).

fold(_, FinalValue, [], FinalValue).
fold(Pred, StartValue, [H | T], FinalValue) :-
    Func =.. [Pred, StartValue, H, Res],
    Func,
    fold(Pred, Res, T, FinalValue).

separate(List, Pred, Y, N) :- separate(List, Pred, Y, N, [], []).

separate([], _, Y, N, Y, N).
separate([H | T], Pred, Y, N, AccY, AccN) :-
    Func =.. [Pred, H],
    Func, !,
    append(AccY, [H], AccY1),
    separate(T, Pred, Y, N, AccY1, AccN).

separate([H | T], Pred, Y, N, AccY, AccN) :-
    append(AccN, [H], AccN1),
    separate(T, Pred, Y, N, AccY, AccN1).

ask_execute :-
    write('What do you want to execute?'),
    nl,
    read(Pred),
    Pred.

my_arg(Index, Term, Arg) :-
    Term =.. [_ | Args],
    nth1(Index, Args, Arg).

my_functor(Term, Name, Arity) :-
    length(Args, Arity),
    Term =.. [Name | Args].

univ(Term, [Name | Args]) :-
    length(Args, NumArgs),
    functor(Term, Name, NumArgs),
    findall(Arg, (between(1, NumArgs, Idx), nth1(Idx, Args, Arg)), Args),
    univ_aux(Term, Args), !.

univ_aux(Term, Args) :- univ_aux(Term, Args, 1).
univ_aux(Term, [], _).
univ_aux(Term, [Arg | T], Counter) :-
    arg(Counter, Term, Arg),
    Counter1 is Counter + 1,
    univ_aux(Term, T, Counter1).
