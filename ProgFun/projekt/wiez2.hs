import Control.Monad
import Data.List
import System.Environment
import Data.Char


-- zewnetrzny fold wypisuje pokolei wyniki, wewnetrzny wiersze wewnatrz 
main = do
	[f,g] <- getArgs
	s     <- readFile f
	let ls = lines s
	let tests = map (\test -> parse (filter (\x -> isDigit x) test) []) ls
	foldr (\t tp -> printResult t >> tp) (putStr "") tests
		

split 0 r a = (reverse r, a)
split n (h:t) a = split (n-1) t (h:a)

parse [x] a = (f, s, n)
	where 
		n = digitToInt x
		(f,s) = split n a []
parse (f:s:t) a =
	parse t ((digitToInt f, digitToInt s):a)



printRow ((l, p), row) = do
	putStr $show l
	putStr " "
	putStr $show row	
	putStr " "
	print p
	return ()

printKol k = do
	putStr " "
	putStr $show k
	return ()


printBoard k rows = do
	putStr "  "
	foldr(\k kp -> printKol k >> kp) (putStrLn "") $fst (unzip k)
	foldr(\row rp -> printRow row >> rp) (putStr "") rows
	putStr "  "
	foldr(\k kp -> printKol k >> kp) (putStr "") $snd (unzip k)
	putStrLn ""
	return ()

printResult (w, k, n) = do 
	putStrLn "Rozpoczynam test kolejny test: "
	print test
	putStr "Znalazłem "
	putStr (show $length results)
	putStrLn " wynikow"
	foldr (\b bp -> printBoard k (zip w b) >> bp) (putStrLn "")  results
	return ()
	where 
		test = (w, k, n)
		results = wiezowce test



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

makeSet set 0 col n= 
	if x == n && foldr (\x y -> n /= x && y) True col then
		[(x:col, filter (x/=) set)]
	else
		[]
	where x = maximum set 
makeSet set limit col _ = map (\x -> (x:col, filter (x /= ) set)) $filter (\x -> foldr (\e b -> x/= e && b) True col && limit >= x) set -- foldr robi za !member

check (l,r) row =
	(check_aux l row 0 0 && check_aux r (reverse row) 0 0)
	
check_aux g [] _ a = a == g
check_aux g (h:t) max a =
	if h > max then
		check_aux g t h (a+1)
	else
		check_aux g t max a

fillRow [] [] [] _ = [[]]
fillRow set (l:ls) (k:ks) n = 
	do
		(newKol, newSet) <- makeSet set l k n
		rest <- fillRow newSet ls ks n
		return (newKol:rest)
	
makeCols desc rowL formKols n= 
	do 
		kols <- fillRow [1..n] rowL formKols n
		guard $check desc $foldr (\x y -> (head x):y) [] kols
		return kols

wiezowce (w, k, n) = 
	do
		board <- map (transpose.reverse.transpose) $makeBoard k limits n cols
		guard $foldr (\x y -> (unique x 0 all) && y) True board
		guard $foldr (\x y -> (unique x 0 all) && y) True (transpose board)
		guard (foldr (\x y -> (uncurry check x) && y) True (zip w board))
		guard (foldr (\x y -> (uncurry check x) && y) True (zip k $transpose board))  
		return board
	where 
		limits = transpose ( boundBoard w k 1 n )
		cols = emptyCols n
		all = sum [1..n]
		
--makeBoard :: [(Integer, Integer)] -> [[Integer]] -> Integer -> [[Integer]] -> [[[Integer]]]	
makeBoard [] [] _ a = [a]
makeBoard (k:ks) (l:ls) n form=
	do
		newCols <- makeCols k l form n 
		board <- makeBoard ks ls n newCols
		return board

emptyCols 0 = []
emptyCols n = []: emptyCols (n-1)
		
unique [] a n = a == n
unique (x:xs) a n = unique xs (x+a) n

test1 = ([ (2, 2), (1, 3), (2, 2), (3, 1)], [ (2, 2), (3, 2), (1, 2), (4, 1)], 4)
test2 = ([ (3, 1), (1, 3), (3, 2), (2, 3)], [ (2, 2), (2, 1), (3, 2), (1, 3)], 4)
test3 = ([ (1, 3), (3, 2), (2, 3), (4, 1), (3, 2)], [ (1, 3), (3, 2), (2, 3), (4, 1), (3, 2)], 5)
test4 = ([ (2, 2), (1, 4), (2, 3), (2, 2), (3, 1)], [ (2, 3), (3, 3), (1, 4), (2, 2), (2, 1)], 5)
test5 = ([ (2, 2), (2, 2), (3, 1), (1, 3), (3, 2)], [ (3, 2), (1, 2), (4, 1), (2, 3), (2, 2)], 5)
test6 = ([ (1, 3), (2, 4), (3, 1), (3, 2), (3, 3), (2, 3)], [ (1, 2), (2, 4), (4, 1), (3, 2), (2, 2), (2, 3)], 6)
test7 = ([ (2, 1), (3, 2), (2, 2), (2, 4), (1, 3), (2, 3)], [ (2, 2), (3, 3), (4, 1), (3, 2), (2, 3), (1, 3)], 6)

testPack = [test1, test2, test3, test4, test5, test6, test7]

test8 =  ([ (2, 2), (1, 3), (2, 2), (3, 1)], [ (2, 2), (3, 2), (1, 2), (4, 1)], 4)
test9 =  ([ (3, 1), (1, 3), (3, 2), (2, 3)], [ (2, 2), (2, 1), (3, 2), (1, 3)],4)
test10 = ([(1, 3), (3, 2), (2, 3), (4, 1), (3, 2)], [ (1, 3), (3, 2), (2, 3), (4, 1), (3, 2)], 5)
test11 = ([ (2, 2), (1, 4), (2, 3), (2, 2), (3, 1)], [ (2, 3), (3, 3), (1, 4), (2, 2), (2, 1)], 5)
test12 = ([ (2, 2), (2, 2), (3, 1), (1, 3), (3, 2)], [ (3, 2), (1, 2), (4, 1), (2, 3), (2, 2)], 5)
test13 = ([ (1, 3), (2, 4), (3, 1), (3, 2), (3, 3), (2, 3)], [ (1, 2), (2, 4), (4, 1), (3, 2), (2, 2), (2, 3)], 6)
test14 = ([ (2, 1), (3, 2), (2, 2), (2, 4), (1, 3), (2, 3)], [ (2, 2), (3, 3), (4, 1), (3, 2), (2, 3), (1, 3)], 6)
test15 = ([ (2, 4), (3, 2), (1, 4), (3, 1), (2, 4), (3, 3), (3, 2), (2, 3)], [ (2, 3), (3, 3), (4, 1), (1, 3), (2, 2), (3, 2), (4, 2), (3, 2)], 8)
