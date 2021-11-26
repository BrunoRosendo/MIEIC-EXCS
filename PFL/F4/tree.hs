data Arv a = Vazia | No a (Arv a) (Arv a)

sumArv :: Num a => Arv a -> a
sumArv Vazia = 0
sumArv (No n left right) = n + sumArv left + sumArv right

nivel :: Int -> Arv a -> [a]
nivel _ Vazia = []
nivel 0 (No x _ _) = [x]
nivel n (No _ left right) = nivel (n - 1) left ++ nivel (n - 1) right
