--Dawid Szczyrk

--1
split xs =
	aux xs xs where
		aux (h1:t1) (_:_:t2) = (h1:zs, ps) where (zs,ps) = aux t1 t2
		aux xs _ = ([], xs) 

merge xs [] = xs
merge [] zs = zs
merge (x:xs) (z:zs) 
	| x < z = x:(merge xs (z:zs))
	| otherwise = z:(merge (x:xs) zs)  


mergesort [] = []		
mergesort [x] = [x]
mergesort (x:xs) = merge (mergesort a) (mergesort b) where (a,b) = split (x:xs)	


x = mergesort [1,6,2,4,89,1,2]
y = mergesort [5,8,7,2,4,1]
