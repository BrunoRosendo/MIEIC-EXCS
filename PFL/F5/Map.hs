module Map where

data Map k a = Empty | Node k a (Map k a) (Map k a)

empty :: Map k a
empty = Empty

insert :: Ord k => k -> a -> Map k a -> Map k a
insert key val Empty = Node key val Empty Empty
insert key val (Node k2 v2 left right)
    | key == k2 = Node k2 v2 left right -- Already exists
    | key < k2 = Node k2 v2 (insert key val left) right
    | otherwise = Node k2 v2 left (insert key val right)

lookupMap :: Ord k => k -> Map k a -> Maybe a
lookupMap _ Empty = Nothing
lookupMap key (Node k2 v2 left right)
    | key == k2 = Just v2
    | key < k2 = lookupMap key left
    | otherwise = lookupMap key right
