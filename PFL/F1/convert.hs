converte20 :: Int -> String
converte20 a = case a of
            0 -> "zero"
            1 -> "um"
            2 -> "dois"
            3 -> "tres"
            4 -> "quatro"
            5 -> "cinco"
            6 -> "seis"
            7 -> "sete"
            8 -> "oito"
            9 -> "nove"
            10 -> "dez"
            11 -> "onze"
            12 -> "doze"
            13 -> "treze"
            14 -> "catorze"
            15 -> "quinze"
            16 -> "dezasseis"
            17 -> "dezassete"
            18 -> "dezoito"
            19 -> "dezanove"
            _ -> "erro"

converteDezenas :: Int -> String
converteDezenas a
            | a >= 20 && a <= 29 = "vinte"
            | a <= 39 = "trinta"
            | a <= 49 = "quarente"
            | a <= 59 = "cinquenta"
            | a <= 69 = "sessenta"
            | a <= 79 = "setenta"
            | a <= 89 = "oitenta"
            | a <= 99 = "noventa"
            | otherwise = "erro"

converte100 :: Int -> String
converte100 a
          | a > 100 = "erro"
          | a < 20 = converte20 a
          | modulo == 0 = dezenas
          | otherwise = dezenas ++ " e " ++ unidades
          where modulo = a `mod` 10
                unidades = converte20 modulo
                dezenas = converteDezenas a

converteCentenas :: Int -> String
converteCentenas a
            | a == 100 = "cem"
            | a > 100 && a <= 199 = "cento"
            | a <= 299 = "duzentos"
            | a <= 399 = "trezentos"
            | a <= 499 = "quatrocentos"
            | a <= 599 = "quinhentos"
            | a <= 699 = "seiscentos"
            | a <= 799 = "setecentos"
            | a <= 899 = "oitocentos"
            | a <= 999 = "novecentos"
            | otherwise = "erro"

converte1000 :: Int -> String
converte1000 a
          | a > 1000 = "erro"
          | a < 100 = converte100 a
          | modulo == 0 = centenas
          | otherwise = centenas ++ " e " ++ dezenas
          where modulo = a `mod` 100
                dezenas = converte100 modulo
                centenas = converteCentenas a

converte :: Int -> String
converte a
          | a > 1000000 = "Limite excedido: max de um milhao"
          | a < 1000 = converte1000 a
          | a == 1000 = "mil"
          | modulo == 0 = milhares
          | otherwise = milhares ++ " e " ++ centenas
          where modulo = a `mod` 1000
                milhares = converte1000 (a `div` 1000) ++ " mil"
                centenas = converte1000 modulo
