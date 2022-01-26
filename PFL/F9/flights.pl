:-dynamic flight/6.
:-use_module(library(lists)).

%flight(origin, destination, company, code, hour, duration)
flight(porto, lisbon, tap, tp1949, 1615, 60).
flight(lisbon, madrid, tap, tp1018, 1805, 75).
flight(lisbon, paris, tap, tp440, 1810, 150).
flight(lisbon, london, tap, tp1366, 1955, 165).
flight(london, lisbon, tap, tp1361, 1630, 160).
flight(porto, madrid, iberia, ib3095, 1640, 80).
flight(madrid, porto, iberia, ib3094, 1545, 80).
flight(madrid, lisbon, iberia, ib3106, 1945, 80).
flight(madrid, paris, iberia, ib3444, 1640, 125).
flight(madrid, london, iberia, ib3166, 1550, 145).
flight(london, madrid, iberia, ib3163, 1030, 140).
flight(porto, frankfurt, lufthansa, lh1177, 1230, 165).

get_all_nodes(ListOfAirports) :-
    setof(
        Airport,
        _A^_B^_C^_D^_E^_F^_G^_H^_I^_J^(
            flight(Airport, _A, _B, _C, _D, _E) ;
            flight(_F, Airport, _G, _H, _I, _J)
        ),
        ListOfAirports
    ).

find_flights(Origin, Destination, Flights) :- find_flights(Origin, Destination, Flights, []), !.
find_flights(Destination, Destination, Flights, Flights).
find_flights(Origin, Destination, Flights, Acc) :-
    flight(Origin, Mid, _, Code, _, _),
    \+ member(Code, Acc),
    append(Acc, [Code], Acc1),
    find_flights(Mid, Destination, Flights, Acc1).

find_flights_breadth(Origin, Destination, Flights) :-
    find_flights_breadth([null-Origin-null], Destination, Flights, []).

find_flights_breadth([Code-Destination-Parent | _], Destination, Flights, Visited) :-
    get_bfs_path(Code-Parent, Visited, Flights).

find_flights_breadth([OCode-Origin-Parent | Rest], Destination, Flights, Visited) :-
    findall(
        Code-Mid-OCode,
        (
            flight(Origin, Mid, _, Code, _, _),
            \+ member(Code-_, Visited),
            \+ member(Code-Mid-_, [OCode-Origin-Parent | Rest])
        ),
        NewNodes
    ),
    append(Rest, NewNodes, Queue),
    find_flights_breadth(Queue, Destination, Flights, [OCode-Parent | Visited]).

get_bfs_path(Current, Visited, Flights) :- get_bfs_path(Current, Visited, Flights, []).
get_bfs_path(null-_, _, Flights, Flights).
get_bfs_path(Code-Parent, Visited, Flights, Acc) :-
    nth0(_, Visited, Parent-NextCode),
    get_bfs_path(Parent-NextCode, Visited, Flights, [Code | Acc]).

find_circular_trip(MaxSize, Origin, Cycle) :-
    find_flights_breadth(Origin, Origin, Cycle),
    length(Cycle, Len), Len < MaxSize, Len > 0, !.
