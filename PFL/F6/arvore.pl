:-dynamic male/1, female/1, parent/2.

male('George').
male('Poppy').
male('Dylan').
female('Haley').
male('Alex').
male('Luke').
female('Lily').
male('Rexford').
female('Claire').
male('Calhoun').
male('Mitchell').
male('Phil').
female('Cameron').
male('Joe').
female('Pameron').
male('Manny').
female('Grace').
male('Bo').
female('DeDe').
male('Frank').
female('Gloria').
male('Jay').
male('Javier').
female('Barb').
male('Perle').

parent('Grace', 'Phil').
parent('Frank', 'Phil').
parent('DeDe', 'Claire').
parent('DeDe', 'Mitchell').
parent('Jay', 'Claire').
parent('Jay', 'Mitchell').
parent('Jay', 'Joe').
parent('Gloria', 'Joe').
parent('Gloria', 'Manny').
parent('Javier', 'Manny').
parent('Barb', 'Cameron').
parent('Barb', 'Pameron').
parent('Merle', 'Cameron').
parent('Merle', 'Pameron').
parent('Phil', 'Haley').
parent('Claire', 'Haley').
parent('Phil', 'Alex').
parent('Claire', 'Alex').
parent('Phil', 'Luke').
parent('Claire', 'Luke').
parent('Mitchell', 'Lily').
parent('Mitchell', 'Rexford').
parent('Cameron', 'Lily').
parent('Cameron', 'Rexford').
parent('Pameron', 'Calhoun').
parent('Bo', 'Calhoun').
parent('Dylan', 'George').
parent('Dylan', 'Poppy').
parent('Haley', 'George').
parent('Haley', 'Poppy').

% parent(X, Y), parent(Y, 'Lily').
% parent('Jay', X), parent(_Y, X), _Y \= 'Gloria', _Y \= 'Jay'.
% parent('Jay', X), \+parent('Gloria', X).

father(X, Y) :- male(X), parent(X, Y).
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).
grandmother(X, Y) :- female(X), grandparent(X, Y).
siblings(X, Y) :- parent(Z, X), parent(Z, Y), parent(W, X), parent(W, Y), Z \= W.
halfSiblings(X, Y) :- parent(Z, X), parent(Z, Y), \+ siblings(X, Y).
