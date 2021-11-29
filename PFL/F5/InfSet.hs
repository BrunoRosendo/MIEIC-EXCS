module InfSet where

data InfSet a = Empty | InfSet (a -> Bool)

empty :: InfSet a
empty = Empty

create :: (a -> Bool) -> InfSet a
create f = InfSet f

member :: Ord a => a -> InfSet a -> Bool
member _ Empty = False
member arg (InfSet f) = f arg

