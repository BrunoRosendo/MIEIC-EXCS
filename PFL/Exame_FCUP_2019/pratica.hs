-- 2

notaF :: [Float] -> [Float] -> Float
notaF notas pesos = sum [x*y | (x, y) <- zip notas pesos]

rfc :: [[Float]] -> Int
rfc notas = length [xs | xs <- notas, any (< 8) xs]


-- 3

type Vert = Int
type Graph = [(Vert, Vert)]

transitiva :: Graph -> Bool
transitiva [] = False
transitiva ((v1, v2):g) = findFirstV v2 g || findSecondV v1 g || transitiva g

findFirstV :: Vert -> Graph -> Bool
findFirstV _ [] = False
findFirstV v ((v1, _) : g) = v == v1 || findFirstV v g

findSecondV :: Vert -> Graph -> Bool
findSecondV _ [] = False
findSecondV v ((_, v2) : g) = v == v2 || findSecondV v g


-- 4

myiterate :: (a -> a) -> a -> [a]
myiterate f first = lista
  where lista = first : [f x | x <- lista]

-- 5

deleteNthRecur :: Int -> [a] -> [a]
deleteNthRecur i xs
  | length xs < i = xs
  | otherwise = take (i - 1) xs ++ deleteNthRecur i (drop i xs)

deleteNthLists :: Int -> [a] -> [a]
deleteNthLists i xs = [ xs !! (n - 1) | n <- [1..length xs], n `mod` i /= 0]

-- 6

data Arv a = Folha | No a (Arv a) (Arv a)

soma :: Num a => Arv a -> a
soma Folha = 0
soma (No n left right) = n + soma left + soma right

somaArv :: Num a => Arv a -> Arv a -> Arv a
somaArv tree Folha = tree
somaArv Folha tree = tree
somaArv (No n1 left1 right1) (No n2 left2 right2) = No (n1 + n2) (somaArv left1 left2) (somaArv right1 right2)

