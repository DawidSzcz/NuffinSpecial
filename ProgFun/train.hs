import Data.Char

comp_turn (0:xs) = 0:(comp_turn xs)
comp_turn (x:xs) = (x-1):xs 
