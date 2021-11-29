module Arv where

data Arv a = Vazia | No a (Arv a) (Arv a)

sumArv :: Num a => Arv a -> a
sumArv Vazia = 0
sumArv (No n left right) = n + sumArv left + sumArv right

nivel :: Int -> Arv a -> [a]
nivel _ Vazia = []
nivel 0 (No x _ _) = [x]
nivel n (No _ left right) = nivel (n - 1) left ++ nivel (n - 1) right

mapArv :: (a -> b) -> Arv a -> Arv b
mapArv _ Vazia = Vazia
mapArv f (No a left right) = No (f a) (mapArv f left) (mapArv f right)

procurar :: Ord a => a -> Arv a -> Bool
procurar x Vazia = False -- não ocorre
procurar x (No y esq dir)
        | x==y = True -- encontrou
        | x<y = procurar x esq -- procura à esquerda
        | x>y = procurar x dir -- procura à direita

inserir :: Ord a => a -> Arv a -> Arv a
inserir x Vazia = No x Vazia Vazia
inserir x (No y esq dir)
        | x==y = No y esq dir -- já ocorre; não insere
        | x<y = No y (inserir x esq) dir -- insere à esquerda
        | x>y = No y esq (inserir x dir) -- insere à direita

construir :: Ord a => [a] -> Arv a
construir [] = Vazia
construir (x:xs) = inserir x (construir xs)

construir2 :: Ord a => [a] -> Arv a
construir2 = foldr inserir Vazia

altura :: Arv a -> Int
altura Vazia = 0
altura (No _ left right) = 1 + max (altura left) (altura right)

maisDir :: Arv a -> a
maisDir Vazia = error "arvore vazia"
maisDir (No x _ Vazia) = x
maisDir (No _ _ right) = maisDir right

remover :: Ord a => a -> Arv a -> Arv a
remover x Vazia = Vazia -- não ocorre
remover x (No y Vazia dir) -- um descendente
        | x==y = dir
remover x (No y esq Vazia) -- um descendente
        | x==y = esq
remover x (No y esq dir) -- dois descendentes
        | x<y = No y (remover x esq) dir
        | x>y = No y esq (remover x dir)
        | x==y = let z = maisDir esq
        in No z (remover z esq) dir
