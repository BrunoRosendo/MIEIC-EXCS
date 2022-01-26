:- op(170, fx, flight).
:- op(180, xfy, from).
:- op(180, xfy, to). % x means associative to lower precedence
:- op(180, xfx, at).
:- op(170, xfx, :).

flight tp1949 from porto to lisbon at 16:15.

:- op(910, fy, if).
:- op(910, xfy, then).
:- op(910, xfx, else).

if Cond then First else _ :- Cond, First.
if _ then _ else Second :- Second.

if (3<4) then write(menor) else write(maior).


% Lists

% Exists in
:- op(300, xfx, exists_in).
Elem exists_in List :- member(Elem, List).

% Append to results
:- op(280, fx, append).
:- op(290, xfx, to).
:- op(290, yfx, results).

append A to B results C :- append(A, B, C).

% Remove from results
:- op(280, fx, remove).
:- op(290, xfx, from).
:- op(290, yfx, results).

remove Elem from List results Result :- delete(List, Elem, Result).
