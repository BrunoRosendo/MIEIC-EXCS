primos :: [Int]
primos = crivo [2..]

crivo :: [Int] -> [Int]
crivo (p:xs) = p : crivo [x | x<-xs, x`mod`p/=0]

fatoresAux :: Int -> [Int] -> [Int] -> [Int]
fatoresAux 1 _ fat = fat
fatoresAux n prime fat
        | n `mod` next == 0 = fatoresAux (n `div` next) prime (next:fat)
        | otherwise = fatoresAux n (tail prime) fat
        where next = head prime

fatores :: Int -> [Int]
fatores n = fatoresAux n prime []
  where prime = reverse (takeWhile (<= n) primos)

calcPi1 :: Int -> Double
calcPi1 n = sum (take n (zipWith (/) num den))
  where den = [1, 3..]
        num = cycle [4, -4]


calcPi2 :: Int -> Double
calcPi2 n = 3 + sum (take n (zipWith (/) num den))
  where num = cycle [4, -4]
        den = map (\x -> x * (x + 1) * (x + 2)) [2..]

charToIdx :: Char -> Int
charToIdx c
            | ascii <= 90 = ascii - 65
            | otherwise = ascii - 97
        where ascii = fromEnum c

cifraChave :: String -> String -> String
cifraChave key text = [toEnum(n + 65) :: Char | n <- zipped]
  where offsets = cycle [charToIdx c | c <- key]
        original = [charToIdx c | c <- text]
        zipped = zipWith (\x y -> (x + y) `mod` 26) original offsets

binom :: Int -> Int -> Int
binom n k
        | k < n - k = div (product [n-k+1..n]) (product [1..k])
        | otherwise = div (product [k+1..n]) (product [1..n-k])

binomFixe :: Int -> Int -> Int
binomFixe n k
        | k == 0 || k == n = 1
        | otherwise = binomFixe (n - 1) (k - 1) + binomFixe n (k + 1)

pascal :: [[Int]]
pascal = [[binomFixe n k | k<-[0..n]] | n<-[0..]]

intercalar :: a -> [a] -> [[a]]
intercalar x ys = [ take i ys ++ [x] ++ reverse (take (length ys - i) (reverse ys)) | i <- [0 .. length ys]]

perms :: [a] -> [[a]]
perms [] = []
perms [x] = [[x]]
perms (x:xs) = concatMap (intercalar x) (perms xs)
