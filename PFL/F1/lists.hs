metades :: [a] -> ([a], [a])
metades list = (take mid list, drop mid list)
                where mid = div (length list) 2

last2 :: [a] -> a
last2 list = list !! (length list - 1)
--last2 list = head (reverse list) -- alternative
--last 2 list = head (drop (length list - 1) list) -- alternative

init2 :: [a] -> [a]
init2 list = take (length list - 1) list
--init2 list = reverse (tail (reverse list)) -- alternative
