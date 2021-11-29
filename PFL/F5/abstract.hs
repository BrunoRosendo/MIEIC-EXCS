import Stack

parent :: String -> Bool
parent s = parentAux s empty

reverseX :: Char -> Char
reverseX '(' = ')'
reverseX '[' = ']'
reverseX '{' = '}'
reverseX ')' = '('
reverseX ']' = '['
reverseX '}' = '{'
reverseX _ = ' '

parentAux :: String -> Stack Char -> Bool
parentAux [] stk = isEmpty stk
parentAux (x:xs) stk
    | x == '(' || x == '[' || x == '{' = parentAux xs (push x stk)
    | x == ')' || x == ']' || x == '}' = not (isEmpty stk) &&
                  top stk == reverseX x &&
                  parentAux xs (pop stk)
    | otherwise = parentAux xs stk

calc :: Stack Float -> String -> Stack Float
calc stk "+" = push (fst + snd) (pop (pop stk))
  where fst = top stk
        snd = top (pop stk)

calc stk "-" = push (fst - snd) (pop (pop stk))
  where fst = top stk
        snd = top (pop stk)

calc stk "*" = push (fst * snd) (pop (pop stk))
  where fst = top stk
        snd = top (pop stk)

calc stk "/" = push (fst / snd) (pop (pop stk))
  where fst = top stk
        snd = top (pop stk)

calc stk arg = push num stk
  where num = read arg :: Float


calcular :: String -> Float
calcular expr = top (foldl calc empty args)
  where args = words expr

rpn :: IO Float
rpn = do
    calcular <$> getLine
