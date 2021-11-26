binom :: Integer -> Integer -> Integer
binom n k = div (product [1..n]) (product [1..k] * product [1..(n-k)])

binom' :: Integer -> Integer -> Integer
binom' n k
        | k < n - k = div (product [n-k+1..n]) (product [1..k])
        | otherwise = div (product [k+1..n]) (product [1..n-k])

raizes :: Float -> Float -> Float -> (Float, Float)
raizes a b c = (
    (-b + sqrt delta) / (2 * a),
    (-b - sqrt delta) / (2 * a)
  )
  where delta = b ** 2 - 4 * a * c
