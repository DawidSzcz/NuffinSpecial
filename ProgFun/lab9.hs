-- Dawid Szczyrk

import Control.Monad.State
data Tree a = Leaf a | Branch (Tree a ) (Tree a)
	deriving (Eq, Ord, Show)


-- Zad 1
label a =  t
	where (t, _) = aux  0 a


aux n (Leaf  x) = (Leaf(x, n), n +1)
aux n (Branch t1 t2) = ((Branch t12 t22), n2)
	where (t12, n1) = aux n t1
	      (t22, n2) = aux n1 t2

test1 = let t = Branch (Leaf 'a') (Leaf 'b') in label (Branch t t) 

--Zad 2

mLabel t = evalState (mAux t) 0   

mAux (Leaf x) = do 	s <- get 
			put (s+1)
			return (Leaf (x, s+1) )
mAux (Branch t1 t2) = do	t12 <- (mAux t1)
				t22 <- (mAux t2)
				return (Branch t12 t22)

test2 = let t = Branch (Leaf 'a') (Leaf 'b') in mLabel (Branch t t) 
			
