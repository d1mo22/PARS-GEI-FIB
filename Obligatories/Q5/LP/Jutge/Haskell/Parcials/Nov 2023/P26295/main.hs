import Data.List

main :: IO ()
main = do
  content <- getContents
  let lines = group $ sort $ words content
  let wordCounts = map (\ws -> (head ws, length ws)) lines
  putStr $ unlines [word ++ " " ++ show count | (word, count) <- wordCounts]

type Counters = [(String, Int)]

count :: String -> Counters
count contents = reverse $ foldl folder [] sortedWords
  where
    sortedWords = sort $ words contents

    folder :: Counters -> String -> Counters
    folder [] w = [(w, 1)]
    folder ((w, c) : cs) w1
      | w1 == w = (w, c + 1) : cs
      | otherwise = (w1, 1) : (w, c) : cs