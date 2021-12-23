factorial(0, 1).
factorial(N, F) :- N > 0, N1 is N - 1, factorial(N1, F1), F is N * F1.

fibonacci(0, 0).
fibonacci(1, 1).
fibonacci(N, F) :- N > 1, N1 is N - 1, N2 is N - 2, fibonacci(N1, F1), fibonacci(N2, F2), F is F1 + F2.

isPrime(X) :- Y is X - 1, isPrime(X, Y).
isPrime(X, 1).
isPrime(X, Y) :- X > 1, Y > 0, X > Y, X mod Y =\= 0, Y1 is Y - 1, isPrime(X, Y1).


