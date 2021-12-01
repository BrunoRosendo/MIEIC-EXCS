import Data.Char

myand :: [Bool] -> Bool
myand xs = foldr (&&) True xs

myor :: [Bool] -> Bool
myor xs = foldr (||) False xs

myconcat :: [[a]] -> [a]
myconcat [] = []
myconcat ([]:xs) = myconcat xs
myconcat ((x:xs):xss) = x:myconcat (xs:xss)

myconcat2 :: [[a]] -> [a]
myconcat2 list = [x | xs<-list, x<-xs]

myreplicate :: Int -> a -> [a]
myreplicate 0 _ = []
myreplicate n value = value:myreplicate (n - 1) value

myreplicate2 :: Int -> a -> [a]
myreplicate2 n value = [value | _ <- [1..n]]

myat :: [a] -> Int -> a
myat (x:xs) 0 = x
myat (x:xs) n = myat xs (n - 1)

myat2 :: [a] -> Int -> a
myat2 list n = last (take (n + 1) list)

myelem :: Eq a => a -> [a] -> Bool
myelem _ [] = False
myelem n (x:xs) = n == x || myelem n xs

deleteEqual :: Eq a => a -> [a] -> [a]
deleteEqual a xs = [n | n<-xs, n /= a]

nub :: Eq a => [a] -> [a]
nub [] = []
nub (x:xs) = x:nub (deleteEqual x xs)

intersperse :: a -> [a] -> [a]
intersperse _ [] = []
intersperse _ [x] = [x]
intersperse a (x:xs) = x:a:intersperse a xs

algarismosRev :: Int -> [Int]
algarismosRev a
              | a < 10 = [a]
              | otherwise = (a`mod`10):algarismosRev (div a 10)

algarismos :: Int -> [Int]
algarismos a = reverse (algarismosRev a)

insert :: Ord a => a -> [a] -> [a]
insert a [] = [a]
insert a (x:xs)
              | a <= x = a:x:xs
              | otherwise = x:insert a xs

isort :: Ord a => [a] -> [a]
isort xs = foldr insert [] xs

forte :: String -> Bool
forte pass = and [
  length pass >= 8,
  any isUpper pass,
  any isLower pass,
  any isDigit pass]

toBits :: Int -> [Int]
toBits 0 = []
toBits num = toBits quotient ++ [rest]
  where quotient = num `div` 2
        rest = num `mod` 2

fromBits :: [Int] -> Int
fromBits xs = sum [ 2^i * rev !! i | i <- [0..length xs - 1]]
  where rev = reverse xs

mdc :: Integer -> Integer -> Integer
mdc a 0 = a
mdc a b = mdc b (a `mod` b)

minimum2 :: Ord a => [a] -> a
minimum2 [] = error "empty list"
minimum2 [x] = x
minimum2 (x:xs) = min x (minimum2 xs)

delete2 :: Eq a => a -> [a] -> [a]
delete2 _ [] = error "empty list"
delete2 y (x:xs)
  | x == y = xs
  | otherwise = x : delete2 y xs

ssort :: Ord a => [a] -> [a]
ssort [] = []
ssort xs = x : ssort (delete2 x xs)
  where x = minimum2 xs

merge :: Ord a => [a] -> [a] -> [a]
merge [] xs = xs
merge xs [] = xs
merge l1 l2
  | n1 < n2 = n1 : merge (tail l1) l2
  | otherwise = n2 : merge l1 (tail l2)
  where n1 = head l1
        n2 = head l2

metades :: [a] -> ([a], [a])
metades list = splitAt mid list
                where mid = div (length list) 2

msort :: Ord a => [a] -> [a]
msort [] = []
msort [x] = [x]
msort xs = merge (msort l1) (msort l2)
  where (l1, l2) = metades xs

addPoly :: [Int] -> [Int] -> [Int]
addPoly list1 list2 = [a + b | (a, b) <- zip ps qs]
  where lenDiff = length list1 - length list2
        ps = list1 ++ replicate (-lenDiff) 0
        qs = list2 ++ replicate lenDiff 0

scalePoly :: Int -> [Int] -> [Int]
scalePoly n list = [n * x | x <- list]

multPoly :: [Int] -> [Int] -> [Int]
multPoly [] _ = []
multPoly _ [] = []
multPoly (x:xs) (y:ys) = reverse (dropWhile (==0) (reverse result))
  where sec = [ x * q | q <- ys]
        thrd = [ y * p | p <- xs]
        next = 0 : multPoly xs ys
        result = (x * y) : addPoly (addPoly sec thrd) next
