funcao :: [a] -> (a -> Bool) -> (a -> a) -> [a]
funcao xs p f = map f (filter p xs)

dec2int :: [Int] -> Int
dec2int = foldl (\x y -> x*10 + y) 0

zipWith2 :: (a -> b -> c) -> [a] -> [b] -> [c]
zipWith2 _ _ [] = []
zipWith2 _ [] _ = []
zipWith2 f (x:xs) (y:ys) = f x y:zipWith2 f xs ys

insert :: Ord a => a -> [a] -> [a]
insert a [] = [a]
insert a (x:xs)
              | a <= x = a:x:xs
              | otherwise = x:insert a xs

isort :: Ord a => [a] -> [a]
isort xs = foldr insert [] xs

maximum1 :: Ord a => [a] -> a
maximum1 = foldl1 max

minimum1 :: Ord a => [a] -> a
minimum1 = foldr1 min

myfoldl1 :: (a -> a -> a) -> [a] -> a
myfoldl1 f xs = foldl f (head xs) (tail xs)

myfoldr1 :: (a -> a -> a) -> [a] -> a
myfoldr1 f xs = foldr f (last xs) (init xs)

mdc :: Integer -> Integer -> Integer
mdc a b = fst (until (\(_, y) -> y==0) (\(x, y) -> (y, x`mod`y)) (a, b))

addList :: [a] -> [a] -> [a]
addList l1 l2 = foldr (:) l2 l1

myconcat :: [[a]] -> [a]
myconcat = foldr (++) []

myreverse1 :: [a] -> [a]
myreverse1 = foldr (\x y -> y ++ [x]) []

myreverse2 :: [a] -> [a]
myreverse2 = foldl (flip (:)) []

myelem :: Eq a => a -> [a] -> Bool
myelem a = any (== a)

auxPalavras :: [String] -> Char -> [String]
auxPalavras xs c
              | c == ' ' = xs ++ [""]
              | otherwise = init xs ++ [last xs ++ [c]]

palavrasRaw :: String -> [String]
palavrasRaw = foldl auxPalavras [""]

palavras :: String -> [String]
palavras frase = filter (/= "") (palavrasRaw frase)

despalavras :: [String] -> String
despalavras = foldl (\acc x -> acc ++ x ++ " ") ""

myscanl :: (b -> a -> b) -> b -> [a] -> [b]
myscanl _ start [] = [start]
myscanl f start (x:xs) = start : myscanl f res xs
 where res = f start x
