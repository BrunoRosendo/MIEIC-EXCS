:-dynamic flight/6.

%flight(origin, destination, company, code, hour, duration)
flight(porto, lisbon, tap, tp1949, 1615, 60).

notMember(Elem, L) :- member(Elem, L), !, fail.

getAllNodes(ListOfAirports) :- getAllNodes(ListOfAirports, []).

getAllNodes(ListOfAirports, Acc) :-
    clause( flight(Air1, Air2, _, _, _, _), _),
    (notMember(Air1, ListOfAirports) ; notMember(Air2, ListOfAirports)),
    append(Acc, Air1, Tmp),
    append(Tmp, Air2, Acc1),
    getAllNodes(ListOfAirports, Acc1).

getAllNodes(ListOfAirports, ListOfAirports).
