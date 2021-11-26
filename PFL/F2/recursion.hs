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

addPoly :: [Int] -> [Int] -> [Int]
addPoly list1 list2 = [a + b | (a, b) <- zip list1 list2]

scalePoly :: Int -> [Int] -> [Int]
scalePoly n list = [n * x | x <- list]




forte :: String -> Bool
forte pass = and [
  length pass >= 8,
  any isUpper pass,
  any isLower pass,
  any isDigit pass]
