--Dawid Szczyrk

--3
data BT a = Empty | Node a (BT a) (BT a)
	deriving(Eq, Ord, Show, Read)

sumBT (Node x t1 t2) = x + sumBT t1 + sumBT t2
sumBT Empty = 0

tree = Node 3 (Node 3 Empty Empty) (Node 5 Empty (Node 6 Empty Empty))

x = (sumBT tree == 17)
--4
foldBT f st Empty = st
foldBT f st (Node x t1 t2) = f x (foldBT f st t1, foldBT f st t2)


--5
foo1 x (y, z) = x + y +z
foo2 x (ys, zs) = x : (ys ++ zs)

y = (foldBT foo1 0 tree == 17)
z = (foldBT foo2 [] tree == [3,3,5,6])

--6
foo3 f x (t1, t2) = Node (f x) t1 t2

mapBT f tree = foldBT (foo3 f) Empty tree

a = 21 == foldBT foo1 0 (mapBT (\x -> x + 1) tree)
