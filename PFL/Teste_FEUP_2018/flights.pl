:- use_module(library(lists)).

airport('Aeroporto Francisco Sa Carneiro', 'LPPR', 'Portugal').
airport('Aeroporto Humberto Delgado', 'LPPT', 'Portugal').
airport('Aeropuerto Adolfo Suarez Madrid-Barajas', 'LEMD', 'Spain').
airport('Aeroport de Paris-Charles-de-Gaulle Roissy Airport', 'LFPG', 'France').
airport('Aeroporto Internazionale di Roma-Fiumicino - Leonardo da Vinci', 'LIRF', 'Italy').

company('TAP', 'TAP Air Portugal', 1945, 'Portugal').
company('RYR', 'Ryanair', 1984, 'Ireland').
company('AFR', 'Societe Air France, S.A.', 1933, 'France').
company('BAW', 'British Airways', 1974, 'United Kingdom').

flight('TP1923', 'LPPR', 'LPPT', 1115, 55, 'TAP').
flight('TP1968', 'LPPT', 'LPPR', 2235, 55, 'TAP').
flight('TP842', 'LPPT', 'LIRF', 1450, 195, 'TAP').
flight('TP843', 'LIRF', 'LPPT', 1935, 195, 'TAP').
flight('FR5483', 'LPPR', 'LEMD', 630, 105, 'RYR').
flight('FR5484', 'LEMD', 'LPPR', 1935, 105, 'RYR').
flight('AF1024', 'LFPG', 'LPPT', 940, 155, 'AFR').
flight('AF1025', 'LPPT', 'LFPG', 1310, 155, 'AFR').

operatesIn(Company, Country) :-
    flight(_, Origin, Destiny, _, _, Company),
    (
        airport(_, Origin, Country) ;
        airport(_, Destiny, Country)
    ).

countries(Company, ListOfCountries) :- countries(Company, ListOfCountries, []).
countries(Company, ListOfCountries, Acc) :-
    operatesIn(Company, Country),
    \+ member(Country, Acc), !,
    append(Acc, [Country], Acc1),
    countries(Company, ListOfCountries, Acc1).
countries(_, ListOfCountries, ListOfCountries) :- !.

mostInternational(ListOfCompanies) :-
    setof(
        Num-Company,
        % Need to ignore extra variables
        Countries^_A^_B^_C^(
            company(Company, _A, _B, _C),
            countries(Company, Countries),
            length(Countries, Num)
        ),
        RawCompanies
    ),
    reverse(RawCompanies, SortedCompanies),
    getMostInternational(SortedCompanies, ListOfCompanies).

getMostInternational(RawCompanies, ListOfCompanies) :- getMostInternational(RawCompanies, ListOfCompanies, []).

getMostInternational([], ListOfCompanies, ListOfCompanies).
getMostInternational([Max-Company | T], ListOfCompanies, []) :-
    getMostInternational(T, ListOfCompanies, [Company], Max).

getMostInternational([Num-Company | T], ListOfCompanies, Acc, Max) :-
    Num = Max, !,
    append(Acc, [Company], Acc1),
    getMostInternational(T, ListOfCompanies, Acc1, Max).

getMostInternational(_, ListOfCompanies, ListOfCompanies, _).
