import Data.Ratio

exps :: Rational -> [Rational]
exps x = zipWith (/) (iterate (* x) 1) (scanl (*) 1 [1 ..])

exponencial :: Rational -> Rational -> Rational
exponencial x e = sum (takeWhile (>= e) (exps x))