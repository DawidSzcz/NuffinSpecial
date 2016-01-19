import Control.Monad
import Data.List


main = print $makeBoard test5

boundBoard [] _ _ _ = []
boundBoard (r:rs) cols y n =
	boundRow r cols (1,y) n : boundBoard rs cols (y+1) n

boundRow _ [] _  _ = []
boundRow (l,r) ((t, b):cols) (x, y) n 
	| l == 1 && x == 1 = 0:row
	| r == 1 && x == n = [0]
	| t == 1 && y == 1 = 0:row
	| b == 1 && y == n = 0:row
	| True = minimum [n - l + x, n - t + y, 2*n - x - r + 1, 2*n - y - b + 1, n] : row
	where row = boundRow (l, r) cols (x+1, y) n 

makeSet set 0 = [(x, filter (x/=) set)]
	where x = maximum set 
makeSet set limit = map (\x -> (x, filter (x /= ) set)) $filter (limit >=) set

makeB [] = [[]]
makeB (row:xs) = foldr (\x y -> (map (x:) next) ++ y) [] row
	where next = makeB xs

check (l,r) row =
	(check_aux l row 0 0 && check_aux r (reverse row) 0 0)
	
check_aux g [] _ a = a == g
check_aux g (h:t) max a =
	if h > max then
		check_aux g t h (a+1)
	else
		check_aux g t max a

fillRow [] []= [[]]
fillRow set (l:ls)= 
	do
		(curr, newSet) <- makeSet set l
		rest <- fillRow newSet ls
		return (curr:rest)
	
makeRow (desc, rowLimits) n = 
	do 
		row <- fillRow [1..n] rowLimits
		guard $check desc row
		return row
		
makeBoard (w, k, n) =
	do
		board <- makeB (map (\x -> makeRow x n) (zip w limits))
		guard $foldr (\x y -> (unique x 0 all) && y) True (transpose board)
		guard (foldr (\x y -> (uncurry check x) && y) True (zip k $transpose board)) 
		return board
	where limits = boundBoard w k 1 n
              all = sum [1..n]
		
		
unique [] a n = a == n
unique (x:xs) a n = unique xs (x+a) n

test1 = ([ (2, 2), (1, 3), (2, 2), (3, 1)], [ (2, 2), (3, 2), (1, 2), (4, 1)], 4)
test2 = ([ (3, 1), (1, 3), (3, 2), (2, 3)], [ (2, 2), (2, 1), (3, 2), (1, 3)], 4)
test3 = ([ (1, 3), (3, 2), (2, 3), (4, 1), (3, 2)], [ (1, 3), (3, 2), (2, 3), (4, 1), (3, 2)], 5)
test4 = ([ (2, 2), (1, 4), (2, 3), (2, 2), (3, 1)], [ (2, 3), (3, 3), (1, 4), (2, 2), (2, 1)], 5)
test5 = ([ (2, 2), (2, 2), (3, 1), (1, 3), (3, 2)], [ (3, 2), (1, 2), (4, 1), (2, 3), (2, 2)], 5)
test6 = ([ (1, 3), (2, 4), (3, 1), (3, 2), (3, 3), (2, 3)], [ (1, 2), (2, 4), (4, 1), (3, 2), (2, 2), (2, 3)], 6)
test7 = ([ (2, 1), (3, 2), (2, 2), (2, 4), (1, 3), (2, 3)], [ (2, 2), (3, 3), (4, 1), (3, 2), (2, 3), (1, 3)], 6)
