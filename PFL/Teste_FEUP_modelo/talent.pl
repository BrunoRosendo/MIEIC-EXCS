:- use_module(library(lists)).

participant(1234, 17, 'Pé coxinho').
participant(3423, 21, 'Programar com os pés').
participant(3788, 20, 'Sing a Bit').
participant(4865, 22, 'Pontes de esparguete').
participant(8937, 19, 'Pontes de pen-drives').
participant(2564, 20, 'Moodle hack').

performance(1234, [120, 120, 120, 120]).
performance(3423, [32, 120, 45, 120]).
performance(3788, [110, 2, 6, 43]).
performance(4865, [120, 120, 110, 120]).
performance(8937, [97, 101, 105, 110]).

madeItThrough(Participant) :-
    performance(Participant, Juri),
    member(120, Juri).

juriTimes(Participants, JuriMember, Times, Total) :-
    participantsTimes(Participants, JuriMember, Times),
    sumlist(Times, Total).

participantsTimes(Participants, JuriMember, Times) :- participantsTimes(Participants, JuriMember, Times, []).

participantsTimes([], _, Times, Times).
participantsTimes([Participant | T], JuriMember, Times, Acc) :-
    performance(Participant, JuriTimes),
    nth1(JuriMember, JuriTimes, Time),
    append(Acc, [Time], Acc1),
    participantsTimes(T, JuriMember, Times, Acc1).

patientJury(JuriMember) :-
    checkJuri(JuriMember, [], Participant),
    checkJuri(JuriMember, [Participant], _).

checkJuri(JuriMember, IgnoreList, Participant) :-
    performance(Participant, Juris),
    \+ member(Participant, IgnoreList),
    nth1(JuriMember, Juris, Time),
    Time = 120.

bestParticipant(P1, P2, P) :-
    performance(P1, Perf1),
    performance(P2, Perf2),

    sumlist(Perf1, Sum1),
    sumlist(Perf2, Sum2),

    bestParticipantBySum(P1, P2, Sum1, Sum2, P).

bestParticipantBySum(P, _, Sum1, Sum2, P) :- Sum1 > Sum2.
bestParticipantBySum(_, P, Sum1, Sum2, P) :- Sum1 < Sum2.

allPerfs :-
    performance(Participant, Juris),
    participant(Participant, _, Talent),
    format('~d:~s:~p~n', [Participant, Talent, Juris]),
    fail.

allPerfs.

equals120(Num) :- Num = 120.

nSuccessfulParticipants(T) :-
    findall(
        Participant,
        (
            performance(Participant, Juris),
            exclude(equals120, Juris, Imperfect),
            Imperfect = []
        ),
        Participants
    ),
    length(Participants, T).

juriFans(JuriFansList) :-
    findall(
        Participant-Fans,
        (
            performance(Participant, Juris),
            findall(
                Fan,
                nth1(Fan, Juris, 120),
                Fans
            )
        ),
        JuriFansList
    ).


eligibleOutcome(Id, Perf, TT) :-
    performance(Id, Times),
    madeItThrough(Id),
    participant(Id, _, Perf),
    sumlist(Times, TT).

nextPhase(N, Participants) :-
    setof(
        Total-Id-Perf,
        Id^Perf^eligibleOutcome(Id, Perf, Total),
        AllParticipants
    ),
    length(AllParticipants, Len),
    Len >= N,
    reverse(AllParticipants, SortedParticipants),
    sublist(SortedParticipants, Participants, 0, N, _).
