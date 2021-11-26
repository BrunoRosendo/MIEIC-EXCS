{-# OPTIONS_GHC -Wno-overlapping-patterns #-}
classifica :: Int -> String
classifica i
          | i <= 9 = "reprovado"
          | i <= 12 = "suficiente"
          | i <= 15 = "bom"
          | i <= 18 = "muito bom"
          | i <= 20 = "muito bom com distincao"
          | otherwise = "bad input"

{-
classifica i = if i <= 9 then "reprovado"
              else if i <= 12 then "suficiente"
              else if i <= 15 then "bom"
              else if i <= 18 then "muito bom"
              else if i <= 20 then "muito bom com distincao"
              else "bad input"
-}

imc :: Float -> Float -> String
imc w h
      | indice < 18.5 = "baixo peso"
      | indice < 25 = "peso normal"
      | indice < 30 = "excesso de peso"
      | otherwise = "obesidade"
      where indice = w / (h**2)

max3 :: Ord a => a -> a -> a -> a
max3 a b = max (max a b)

min3 :: Ord a => a -> a -> a -> a
min3 a b = min (min a b)

xor :: Bool -> Bool -> Bool
xor True a = not a
xor False a = a

safetail :: [a] -> [a]
safetail list
      | null list = []
      | otherwise = tail list

{-
safetail list =
      if null list then []
      else tail list
-}

{-
safetail list | null list = []
safetail list = tail list
-}

curta :: [a] -> Bool
curta list = len >= 0 && len <= 2
             where len = length list

{-
curta (_ : (_ : xs)) = null xs
curta (_ : xs) = null xs
curta list = null list
-}

mediana :: Ord a => a -> a -> a -> a
mediana a b c
      | a > b = if b > c then b
            else if a > c then c
            else a
      | a > c = a
      | b > c = c
      | otherwise = b


mediana2 :: (Num a, Ord a) => a -> a -> a -> a
mediana2 a b c = (a + b + c) - minNum - maxNum
                 where minNum = min3 a b c
                       maxNum = max3 a b c

