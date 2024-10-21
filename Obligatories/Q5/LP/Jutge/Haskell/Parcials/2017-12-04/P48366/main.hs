-- Problema 5 Racionals
data Racional = Racional Integer Integer
  deriving (Eq)

racional :: Integer -> Integer -> Racional
racional x y = Racional (div x m) (div y m)
  where
    m = gcd x y

numerador :: Racional -> Integer
numerador (Racional x _) = x

denominador :: Racional -> Integer
denominador (Racional _ y) = y

instance Show Racional where
  show (Racional x y) = show x ++ "/" ++ show y