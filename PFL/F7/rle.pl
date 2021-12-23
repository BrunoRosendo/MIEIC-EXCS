:-use_module(library(lists)).

encodeChar(C, Word, Rest, Res) :- encodeChar(C, Word, Rest, Res, 0).
encodeChar(C, [C | T], Rest, Res, Acc) :- Acc1 is Acc + 1, encodeChar(C, T, Rest, Res, Acc1).
encodeChar(C, [], [], Acc, Acc).
encodeChar(C, [H | T], [H | T], Acc, Acc) :- C \= H.

rle(L1, L2) :- rle(L1, L2, []).
rle([], Acc, Acc).
rle([H | T], L2, Acc) :-
    encodeChar(H, [H | T], NewL1, Num),
    number_codes(Num, NumString),
    append([H], "-", X1),
    append(X1, NumString, X2),
    append(Acc, [X2], Acc1),
    rle(NewL1, L2, Acc1).

decodeChar(C, Num, String) :- decodeChar(C, Num, String, "").
decodeChar(_, 0, Acc, Acc).
decodeChar(C, Num, String, Acc) :-
    Num > 0,
    Num1 is Num - 1,
    append(Acc, [C], Acc1),
    decodeChar(C, Num1, String, Acc1).

un_rle(L1, L2) :- un_rle(L1, L2, "").
un_rle([], Acc, Acc).
un_rle([ [C, _ | Freq] | T], L2, Acc) :-
    number_codes(Num, Freq),
    decodeChar(C, Num, String),
    append(Acc, String, Acc1),
    un_rle(T, L2, Acc1).
