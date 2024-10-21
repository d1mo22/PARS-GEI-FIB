{-# OPTIONS_GHC -Wno-noncanonical-monad-instances #-}

data Queue a = Queue [a] [a]
  deriving (Show)

instance Functor Queue where
  fmap f (Queue [] []) = Queue [] []
  fmap f (Queue as bs) = Queue (map f as) (map f bs)

instance Applicative Queue where
  pure x = Queue [x] []
  f <*> queue = Queue (q2l f <*> q2l queue) []

instance Monad Queue where
  -- Envuelve el valor en una Queue (de x hace una queue con x)
  return x = Queue [x] []
  q >>= f = Queue l []
    where
      l = q2l q >>= (q2l . f)

translation :: (Num b) => b -> Queue b -> Queue b
translation b = fmap (+ b)

kfilter :: (p -> Bool) -> Queue p -> Queue p
kfilter f queue = do
  q <- queue
  if f q
    then return q
    else Queue [] []

q2l :: Queue a -> [a]
q2l (Queue as bs) = as ++ reverse bs

create :: Queue a
create = Queue [] []

push :: a -> Queue a -> Queue a
push x (Queue as bs) = Queue as (x : bs)

pop :: Queue a -> Queue a
pop (Queue [] bs) = Queue (tail (reverse bs)) []
pop (Queue (a : as) bs) = Queue as bs

top :: Queue a -> a
top (Queue [] bs) = last bs
top (Queue (a : as) _) = a

empty :: Queue a -> Bool
empty (Queue [] []) = True
empty _ = False

instance (Eq a) => Eq (Queue a) where
  Queue as1 bs1 == Queue as2 bs2 = as1 ++ reverse bs1 == as2 ++ reverse bs2