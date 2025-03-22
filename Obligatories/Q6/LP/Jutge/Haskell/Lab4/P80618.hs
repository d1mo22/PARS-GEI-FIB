data Queue a = Queue [a] [a]
  deriving (Show)

instance (Eq a) => Eq (Queue a) where
  (Queue xs ys) == (Queue xs' ys') = (xs ++ reverse ys) == (xs' ++ reverse ys')

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

c1 = push 4 (pop (push 3 (push 2 (push 1 create))))

c2 = push 4 (push 3 (push 2 create))
