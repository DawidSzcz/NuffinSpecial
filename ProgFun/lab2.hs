--Dawid Szczyrk

--1
powtorz y = foldl (++) [] (map (\x -> (take x (repeat x)))  y)

