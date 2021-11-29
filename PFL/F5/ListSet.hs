module ListSet where

data ListSet a = ListSet [a]

empty :: ListSet a
empty = ListSet []

member :: Ord a => a -> ListSet a -> Bool
member num (ListSet xs) = num `elem` xs

insert :: Ord a => a -> ListSet a -> ListSet a
insert num (ListSet xs)
  | num `elem` xs = ListSet xs
  | otherwise = ListSet (num : xs)

