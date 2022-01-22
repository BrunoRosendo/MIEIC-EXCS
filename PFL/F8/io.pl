print_n(_, 0).

print_n(S, N):-
  write(S),
  N1 is N - 1,
  print_n(S, N1).

put_string([]).
put_string([H | T]) :-
  put_code(H),
  put_string(T).

print_text(Text, Symbol, Padding) :-
  write(Symbol),
  print_n(' ', Padding),
  put_string(Text),
  print_n(' ', Padding),
  write(Symbol).

read_number(X) :- read_number(X, 0).

read_number(X, X) :-
  peek_code(10), !,
  skip_line.

read_number(X, Acc) :-
  get_code(C),
  C >= 48,
  C =< 57, !,
  Real is C - 48,
  Tmp is Acc * 10,
  Acc1 is Tmp + Real,
  read_number(X, Acc1).

read_until_between(Min, Max, Value) :-
  repeat, % until we find the solution
  read_number(Value),
  check_between(Min, Max, Value), !.

check_between(Min, Max, Value) :-
  Value >= Min,
  Value =< Max.

