import Data.Char
import System.Random

print_board [] False = putStr "Wybierz wiersz, lub zero zeby skonczyc ture\n"
print_board [] True = putStr "Ta1k wygląda plansza po ruchu komputera\n"
print_board (x:xs) comp = putChar (intToDigit x) >> putStr ": " >> print_stars x >> print_board xs comp

print_stars x  | x == 0 = putChar '\n'
			   | otherwise = putChar '*' >> print_stars (x-1) 

empty [] = True
empty (0:xs) = empty xs
empty _ = False

start board = player_turn board 

player_turn board 
	| empty board 	 = putStr "Wygrałeś"
	| True	 		 = do{
					print "Tura gracza";
					print_board board False;
					getChar >>= \c -> p_turn c board False
				}

p_turn c board move_made
	| digitToInt c == 0 && move_made 	= comp_turn board
	| digitToInt c == 0 				= putStr "\nNie wykonano ruchu" >> 
				  		  				getChar >>= 
				  		  				\c -> p_turn c board move_made
	| is_valid (digitToInt c) board 	= putStr "\nUsunales gwiazdke z " >> 
				  		  				putChar c >>
						  				putStr " wiersza. Co robisz dalej" >>
						  				(\b -> getChar >>=
						  					\c -> p_turn c b True)(make_move (digitToInt c) board)
	| True		 			= putStr "\nBledny ruch. Jeszcze raz." >> 
						  				getChar >>= 
						  				\c -> p_turn c board move_made 

getRow _ [] acc = randomRIO (1, length acc) >>= \n -> return (head (drop (n-1) acc))
getRow i (0:xs) acc = getRow (i+1) xs acc >>= \n -> return n
getRow i (_:xs)  acc = getRow (i+1) xs (i:acc) >>= \n -> return n

comp_turn board
	| empty board = putStr "\nPrzegrałeś"
	| otherwise	      = do{
							row <- getRow 1 board [];
							newBoard <- sub board row;
							print_board newBoard True;
							putStr "\nKomputer usunął gwiazdkę z ";
 							return row >>= \r -> putChar (intToDigit r);
							putStr " pola";   
							player_turn newBoard;
						}
sub (x:xs) 1 = return ((x-1):xs) 
sub (x:xs) n= sub xs (n-1) >>= \r -> return (x:r)  



is_valid _ [] = False
is_valid i (x:xs)
	| i < 0 			= False
	| i == 1 && x==0  	= False
	| i == 1			= True
	| True				= is_valid (i-1) xs

make_move 1 (x:xs) = (x-1):xs
make_move i (x:xs) = x:make_move (i-1) xs



