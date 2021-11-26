quadrados :: Int
quadrados = sum [x^(2 :: Int) | x<-[1..100]]

dotprod :: [Float] -> [Float] -> Float
dotprod l1 l2 = sum [x * y | (x, y)<- zip l1 l2]

aprox :: Int -> Double
aprox n = 4 * sum [(-1)^x / fromIntegral (2*x + 1) | x<-[0..n]]

aproxBoa :: Int -> Double
aproxBoa n = sqrt (12 * soma)
            where soma = sum [(-1)^k / fromIntegral ((k + 1)^(2 :: Int)) | k<-[0..n]]

divprop :: Integer -> [Integer]
divprop n = [x | x<-[1..n - 1], n`mod`x == 0]

perfeitos :: Integer -> [Integer]
perfeitos n = [x | x<-[1..n], x == sum (divprop x)]

pitagoricos :: Integer -> [(Integer, Integer, Integer)]
pitagoricos n = [(x, y, z) | x<-[1..n], y <-[1..n], z<-[1..n], x^2 + y^2 == z^2]

primo :: Integer -> Bool
primo n
        | n == 1 = True
        | otherwise = null (tail (divprop n))

binom :: Integer -> Integer -> Integer
binom n k
        | k < n - k = div (product [n-k+1..n]) (product [1..k])
        | otherwise = div (product [k+1..n]) (product [1..n-k])

pascal :: Integer -> [[Integer]]
pascal num = [[binom n k | k<-[0..n]] | n<-[0..num]]

cifrarLetra :: Int -> Char -> Char
cifrarLetra n l
                | ascii <= 90 = toEnum ((ascii + n - 65)`mod`26 + 65) :: Char
                | otherwise = toEnum ((ascii + n - 97)`mod`26 + 97) :: Char
                where ascii = fromEnum l

cifrar :: Int -> String -> String
cifrar n word = [cifrarLetra n l | l <- word]

mindiv :: Int -> Int
mindiv n = head ([x | x<-[2..ceiling(sqrt (fromIntegral n))], n`mod`x == 0] ++ [n])

primo2 :: Int -> Bool
primo2 n = n > 1 && mindiv n == n
