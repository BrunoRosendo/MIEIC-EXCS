pitagoricos :: Integral a => a -> a -> a -> Bool
pitagoricos a b c = as + bs == cs
                  || as + cs == bs
                  || bs + cs == as
  where as = a^2
        bs = b^2
        cs = c^2


hipotenusa :: Float -> Float -> Float
hipotenusa a b = sqrt (a**2 + b**2)

diferentesRecur :: Eq a => [a] -> [a]
diferentesRecur [] = []
diferentesRecur [_] = []
diferentesRecur (x:y:xs)
      | x /= y = x : diferentesRecur (y:xs)
      | otherwise = diferentesRecur(y:xs)

diferentesList :: Eq a => [a] -> [a]
diferentesList xs = [x | (x, y) <- zip xs (tail xs), x /= y]

myzip3 :: [a] -> [b] -> [c] -> [(a, b, c)]
myzip3 xs ys zs = [ (x, y, z) | ((x, y), z) <- rawZip]
      where rawZip = zip (zip xs ys) zs

partir :: Eq a => a -> [a] -> ([a], [a])
partir _ [] = ([], [])
partir n (x:xs)
      | n == x = ([], x:xs)
      | otherwise = (x : fstNext, sndNext)
      where (fstNext, sndNext) = partir n xs

concatAll :: [a] -> [[a]] -> [[a]]
concatAll [] res = res
concatAll (x:xs) [] = concatAll xs [[x]]
concatAll (x:xs) ys = concatAll xs (ys ++ [last ys ++ [x]])

perms :: [a] -> [[[a]]]
perms [] = [[]]
perms [x] = [[[x]]]
perms xs = concat (zipWith zipPerms concats maps)
      where concats = concatAll xs []
            maps = map (\cur -> perms (drop (length cur) xs)) concats

zipPerms :: [a] -> [[[a]]] -> [[[a]]]
zipPerms xs ys = [xs : y | y <- ys]
