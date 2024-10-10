import System.Posix (ControlCharacter (Quit), badSystemCall)

data Queue a = Queue [a] [a]
  deriving (Show)

create :: Queue a
create = Queue [] []

push :: a -> Queue a -> Queue a
push x (Queue as bs) = Queue as (x : bs)

pop :: Queue a -> Queue a
pop (Queue [] []) = Queue [] []
pop (Queue [] bs) = Queue (tail (reverse bs)) []
pop (Queue (a : as) bs) = Queue as bs

top :: Queue a -> a
top (Queue [] bs) = last bs
top (Queue (a : as) bs) = a

empty :: Queue a -> Bool
empty (Queue [] []) = True
empty _ = False

instance (Eq a) => Eq (Queue a) where
  (Queue as1 bs1) == (Queue as2 bs2) = (as1 ++ reverse bs1) == (as2 ++ reverse bs2)