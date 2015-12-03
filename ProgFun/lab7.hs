import Data.Char

start board = start_turn 1 board 

star_turn player board = putStr "Tura gracza " >> putCar (intToDigit player ) >> print_board >> turn board false

print_board [] = putStr "Wybierz wiersz, lub zero zeby skonczyc ture\n"
print_board (x:xs) = putChar (intToDigit x) >> putStr ": " >> print_stars x >> print_board xs

print_stars 0 = putChar '\n'
print_stars n = putChar '*' >> print_stars (n-1) 

turn board made_move = getChar >>= isValid board made_move (\c -> digitToint c) ->

isValid board false 0 = putStr "Nie wykonano ruchu" >> turn board false
isValid board true 0 = start_turn 2-
