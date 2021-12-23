:-use_module(library(lists)).

list_from_to(Inf, Sup, List) :- list_from_to(Inf, Sup, List, []).
list_from_to(Inf, Sup, Acc, Acc) :- Inf > Sup.
list_from_to(Inf, Sup, List, Acc) :-
    Inf =< Sup,
    Inf1 is Inf + 1,
    append(Acc, [Inf], Acc1),
    list_from_to(Inf1, Sup, List, Acc1).

list_from_to_step(Inf, Step, Sup, List) :- list_from_to_step(Inf, Step, Sup, List, []).
list_from_to_step(Inf, Step, Sup, Acc, Acc):- Inf > Sup.
list_from_to_step(Inf, Step, Sup, List, Acc) :- 
    Inf =< Sup,
    Inf1 is Inf + Step,
    append(Acc, [Inf], Acc1),
    list_from_to_step(Inf1, Step, Sup, List, Acc1).

list_from_to2(Inf, Sup, List) :- Sup >= Inf, list_from_to(Inf, Sup, List, []).
list_from_to2(Inf, Sup, List) :- Sup < Inf, list_from_to(Sup, Inf, L1, []), reverse(L1, List).

list_from_to_step2(Inf, Step, Sup, List) :- Sup >= Inf, list_from_to_step(Inf, Step, Sup, List, []).
list_from_to_step2(Inf, Step, Sup, List) :- Sup < Inf, list_from_to_step(Sup, Step, Inf, L1, []), reverse(L1, List).

