data Nat = Z | S Nat deriving (Show)

rec :: a -> (Nat -> a -> a) -> Nat -> a
rec base step Z = base
rec base step (S n) = step n (rec base step n)

isEven :: Nat -> Bool
isEven = rec base step
  where
    base = True
    step n = not

add :: Nat -> (Nat -> Nat)
add = rec base step
  where
    base = id
    step n f m = S (f m)

mul :: Nat -> (Nat -> Nat)
mul = rec base step
  where
    base = const Z
    step n f m = add m (f m)

fact :: Nat -> Nat
fact = rec base step
  where
    base = S Z
    step n = mul (S n)
