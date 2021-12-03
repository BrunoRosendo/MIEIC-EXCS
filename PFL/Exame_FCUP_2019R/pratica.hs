import Data.List (nub)
-- 2

imparDiv3Func :: Integral a => [a] -> Bool
imparDiv3Func = all (\x -> x `mod` 3 /= 0 || odd x)

imparDiv3Lists :: Integral a => [a] -> Bool
imparDiv3Lists xs = null lista
  where lista = [x | x <- xs, x `mod` 3 == 0 && even x]

-- 3

type Rel a = [(a, [a])]

getListByKey :: Eq a => Rel a -> a -> [a]
getListByKey [] _ = []
getListByKey ((k, xs) : rel) n
  | n == k = xs
  | otherwise = getListByKey rel n

comporRelacao :: Eq a => Rel a -> (a, [a])-> (a, [a])
comporRelacao rel (k, xs) = (k, lista)
  where lista = nub (concatMap (getListByKey rel) xs)

composta :: Eq a => Rel a -> Rel a -> Rel a
composta r1 r2 = map (comporRelacao r2) r1

-- 4

gandaLista :: [Int]
gandaLista = 1 : [ 2 * gandaLista !! (i - 2) + i + 1 | i <- [2..]]

-- 5

duplicada :: Eq a => [a] -> Bool
duplicada [] = True
duplicada [_] = False
duplicada (x:y:xs) = x == y && duplicada xs

duplica :: [a] -> [a]
duplica xs = concat [[x, x] | x <- xs]

-- 6

data Arv a = Folha a | No (Arv a) (Arv a)

emOrdem :: Arv a -> [a]
emOrdem (Folha n) =  [n]
emOrdem (No left right) = emOrdem left ++ emOrdem right

anyArv :: (a -> Bool) -> Arv a -> Bool
anyArv f (Folha n) = f n
anyArv f (No left right) = anyArv f left || anyArv f right
