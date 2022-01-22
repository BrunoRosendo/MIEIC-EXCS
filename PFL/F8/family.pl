:- consult('../F6/arvore.pl').

children(Person, Children) :-
    findall(Child, parent(Person, Child), Children).

couple(Mano-Bro) :-
    parent(Mano, X),
    parent(Bro, X),
    Mano @< Bro.

couples(List) :-
    setof(Couple, couple(Couple), List).

couple_two(Mano-Bro) :-
    parent(Mano, X),
    parent(Bro, X),
    parent(Mano, Y),
    parent(Bro, Y),
    X \= Y,
    Mano @< Bro.

parents_of_two(Parents) :-
    setof(Couple, couple_two(Couple), Parents).
