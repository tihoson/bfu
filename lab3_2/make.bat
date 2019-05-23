rem Windows style

set INC=.\inc
set SRC=.\src
set BASIC=\Basic_includes
set MAP=\Map_elements
set ITEMS=\Items
set WEAPON=\Weapon
set OBJ=.\obj
set FMEGA=-I"%INC%%MAP%" -I"%INC%%BASIC%" -I"%INC%%PLAYER%" -I"%INC%%ITEMS%" -I"%INC%%ITEMS%%WEAPON%"

If Not Exist ".\obj" (
	mkdir ".\obj"
)

g++ -std=c++11 %FMEGA% -c "%SRC%%MAP%"\Map_cell.cpp  -o %OBJ%\Map_cell.o
g++ -std=c++11 %FMEGA% -c "%SRC%%MAP%"\Map.cpp  -o %OBJ%\Map.o
g++ -std=c++11 %FMEGA% -c "%SRC%%ITEMS%"\Item.cpp  -o %OBJ%\Item.o
g++ -std=c++11 %FMEGA% -c "%SRC%%ITEMS%%WEAPON%"\Weapon.cpp  -o %OBJ%\Weapon.o
g++ -std=c++11 %FMEGA% -c "%SRC%%ITEMS%%WEAPON%"\Fork.cpp  -o %OBJ%\Fork.o
g++ -std=c++11 %FMEGA% -c "%SRC%%ITEMS%%WEAPON%"\Long_bow.cpp  -o %OBJ%\Long_bow.o
g++ -std=c++11 %FMEGA% -c "%SRC%%ITEMS%%WEAPON%"\Wabbajack.cpp  -o %OBJ%\Wabbajack.o
g++ -std=c++11 %FMEGA% -c "%SRC%"\Player.cpp  -o %OBJ%\Player.o
g++ -std=c++11 %FMEGA% -c "%SRC%"\Game_controller.cpp  -o %OBJ%\Game_controller.o
g++ -std=c++11 %FMEGA% -c "%SRC%"\main.cpp  -o %OBJ%\main.o

g++ -std=c++11 %OBJ%\Map_cell.o %OBJ%\Map.o %OBJ%\Item.o %OBJ%\Weapon.o %OBJ%\Fork.o %OBJ%\Long_bow.o %OBJ%\Wabbajack.o %OBJ%\Player.o %OBJ%\Game_controller.o %OBJ%\main.o -o game
