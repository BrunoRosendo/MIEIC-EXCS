import Arv

data TreeSet a = TreeSet (Arv a)

empty :: TreeSet a
empty = TreeSet Vazia

member :: Ord a => a -> TreeSet a -> Bool
member elem (TreeSet tree) = procurar elem tree

insert :: Ord a => a -> TreeSet a -> TreeSet a
insert elem (TreeSet tree)
    | procurar elem tree = TreeSet tree
    | otherwise = TreeSet (inserir elem tree)

union :: Ord a => TreeSet a -> TreeSet a -> TreeSet a
union (TreeSet tree1) (TreeSet Vazia) = TreeSet tree1
union (TreeSet tree1) (TreeSet tree2) = union (TreeSet (inserir elem tree1)) (TreeSet (remover elem tree2))
  where elem = maisDir tree2

intersect :: Ord a => TreeSet a -> TreeSet a -> TreeSet a
intersect (TreeSet Vazia) _ = TreeSet Vazia
intersect (TreeSet tree1) (TreeSet tree2)
  | procurar elem tree2 = insert elem (TreeSet (remover elem tree1))
  | otherwise = TreeSet (remover elem tree1)
  where elem = maisDir tree1

difference :: Ord a => TreeSet a -> TreeSet a -> TreeSet a
difference set (TreeSet Vazia) = set
difference (TreeSet tree1) (TreeSet tree2) = difference (TreeSet (remover elem tree1)) (TreeSet (remover elem tree2))
  where elem = maisDir tree2
