:- consult('../F6/arvore.pl').
:- consult('../F8/family.pl').

addPerson :-
    write('Gender: '),
    read(Gender),
    nl,
    write('Name. '),
    read(Name),
    addPerson(Gender, Name).

addPerson(male, Person) :- assertz(( male(Person) )).
addPerson(female, Person) :- assertz(( female(Person) )).

removePerson :-
    write('Welcome to Prolog\' Death Note. Who do you want to purge?'),
    nl,
    read(Person),
    retractall(male(Person)),
    retractall(female(Person)),
    retractall(parent(Person, _)),
    retractall(parent(_, Parent)).
