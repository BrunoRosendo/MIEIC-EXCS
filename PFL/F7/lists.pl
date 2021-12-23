inner_product(L1, L2, Result) :- inner_product(L1, L2, Result, 0).
inner_product([], [], Result, Result).
inner_product([H1 | T1], [H2 | T2], Result, Acc) :-
  Acc1 is H1 * H2 + Acc,
  inner_product(T1, T2, Result, Acc1).

count(Elem, List, N) :- count(Elem, List, N, 0).
count(_, [], N, N).
count(Elem, [Elem | T], N, Acc) :- Acc1 is Acc + 1, count(Elem, T, N, Acc1).
count(Elem, [_ | T], N, Acc) :- count(Elem, T, N, Acc).

del_one(Elem, L1, L2) :- del_one(Elem, L1, L2, []).
del_one(Elem, [Elem | T], [Acc | T], Acc).
del_one(Elem, [H | T], L2, Acc) :- append(Acc, H, Acc1), del_one(Elem, T, L2, Acc1).

del_all(Elem, L1, L2) :- del_all(Elem, L1, L2, []).
del_all(Elem, [], Acc, Acc).
del_all(Elem, [Elem | T], L2, Acc) :- del_all(Elem, T, L2, Acc).
del_all(Elem, [H | T], L2, Acc) :- append(Acc, [H], Acc1), del_all(Elem, T, L2, Acc1), Elem \= H.

list_append(L1, L2, L3) :- append(L1, L2, L3).

list_member(Elem, [Elem | _]).
list_member(Elem, [H | T]) :- list_member(Elem, T), Elem \= H.


