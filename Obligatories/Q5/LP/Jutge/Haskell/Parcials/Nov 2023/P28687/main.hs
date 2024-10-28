{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}

{-# HLINT ignore "Use camelCase" #-}

import Data.Ratio

termes_cosinus :: Rational -> [Rational]
termes_cosinus x = (iterate (*) (-1)) * zipWith (/) (iterate (^ 2) 1) (scanl (*))

cosinus :: Rational -> Rational -> Rational
cosinus x e = sum (takeWhile (>= e) termes_cosinus x)