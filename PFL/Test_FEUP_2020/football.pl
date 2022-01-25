jogo(1, sporting, porto, 1-2).
jogo(1, maritimo, benfica, 2-0).
jogo(2, sporting, benfica, 0-2).
jogo(2, porto, maritimo, 1-0).
jogo(3, maritimo, sporting, 1-1).
jogo(3, benfica, porto, 0-2).

treinadores(porto, [[1-3]-sergio_conceicao]).
treinadores(sporting, [[1-2]-silas, [3-3]-ruben_amorim]).
treinadores(benfica, [[1-3]-bruno_lage]).
treinadores(maritimo, [[1-3]-jose_gomes]).

n_treinadores(Equipa, Numero) :-
    treinadores(Equipa, Treinadores),
    length(Treinadores, Numero).

n_jornadas_treinador(Treinador, NumJornadas) :-
    treinadores(_, Treinadores),
    member([Min-Max]-Treinador, Treinadores),
    NumJornadas is Max - Min + 1.

ganhou(Jornada, Vencedor, Derrotado) :-
    jogo(Jornada, Vencedor, Derrotado, VScore-DScore),
    VScore > DScore.

ganhou(Jornada, Vencedor, Derrotado) :-
    jogo(Jornada, Derrotado, Vencedor, DScore-VScore),
    VScore > DScore.

:- op(180, fx, o).
:- op(200, xfx, venceu).

o Equipa :- treinadores(Equipa, _).
o Vencedor venceu o Derrotado :-
    ganhou(_, Vencedor, Derrotado).

treinador_bom(Treinador) :-
    treinadores(Equipa, Treinadores),
    member([Min-Max]-Treinador, Treinadores),
    treinador_bom(Equipa, Max, Min).

treinador_bom(_, Max, Max).
treinador_bom(Equipa, Max, Jornada) :-
    \+ ganhou(Jornada, _, Equipa),
    NewJornada is Jornada + 1,
    treinador_bom(Equipa, Max, NewJornada).

imprime_totobola(1, '1').
imprime_totobola(0, 'X').
imprime_totobola(-1, '2').

imprime_texto(X, 'vitoria da casa') :- X = 1.
imprime_texto(X, 'empate') :- X = 0.
imprime_texto(X, 'derrota da casa') :- X = -1.

imprime_jogos(Pred) :-
    findall(
        (Jornada, Casa, Fora, Resultado),
        jogo(Jornada, Casa, Fora, Resultado),
        Jogos),
    imprime_jogos(Pred, Jogos).

imprime_jogos(_, []).
imprime_jogos(Pred, [(Jornada, Casa, Fora, Resultado) | T]) :-
    get_result(Resultado, Num),
    Term =.. [Pred, Num, Text],
    Term,
    format('Jornada ~d: ~s x ~s - ~s', [Jornada, Casa, Fora, Text]),
    nl,
    imprime_jogos(Pred, T).
    

get_result(Casa-Fora, 1) :- Casa > Fora.
get_result(Res-Res, 0). % draw
get_result(Casa-Fora, -1) :- Casa < Fora.

lista_treinadores(L) :-
    findall(
        Treinador,
        (treinadores(_, Treinadores), member(_-Treinador, Treinadores)),
        L
    ).

duracao_treinadores(L) :-
    setof(
        Duracao-Treinador,
        [Min-Max]^Treinadores^Equipa^(treinadores(Equipa, Treinadores), member([Min-Max]-Treinador, Treinadores), Duracao is Max - Min + 1),
        L
    ).
