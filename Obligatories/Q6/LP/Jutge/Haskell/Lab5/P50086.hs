data Queue a = Queue [a] [a]
  deriving (Show)

instance (Eq a) => Eq (Queue a) where
  (Queue xs ys) == (Queue xs' ys') = (xs ++ reverse ys) == (xs' ++ reverse ys')

instance Functor Queue where
  fmap f (Queue xs ys) = Queue (map f xs) (map f ys)

instance Applicative Queue where
  pure x = Queue [x] []
  f <*> queue = Queue (q2l f <*> q2l queue) []

instance Monad Queue where
  q >>= f = Queue l []
    where
      l = q2l q >>= (q2l . f)

kfilter :: (p -> Bool) -> Queue p -> Queue p
kfilter p queue = do
  q <- queue
  if p q then return q else Queue [] []

translation :: (Num b) => b -> Queue b -> Queue b
translation _ (Queue [] []) = Queue [] []
translation b (Queue xs ys) = Queue (map (+ b) xs) (map (+ b) ys)

q2l :: Queue a -> [a]
q2l (Queue [] []) = []
q2l (Queue xs ys) = xs ++ reverse ys

create :: Queue a
create = Queue [] []

push :: a -> Queue a -> Queue a
push a (Queue xs ys) = Queue xs (a : ys)

pop :: Queue a -> Queue a
pop (Queue [] []) = Queue [] []
pop (Queue [] ys) = Queue (tail $ reverse ys) []
pop (Queue (x : xs) ys) = Queue xs ys

top :: Queue a -> a
top (Queue xs ys)
  | null xs = last ys
  | otherwise = head xs

empty :: Queue a -> Bool
empty (Queue [] []) = True
empty (Queue _ _) = False

c = push 3 (push 2 (push 1 create))
