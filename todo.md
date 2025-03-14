# Parser (he dejado algun print, asi si mañana algo falla para saber en que parte)
1. en color solo acepta numeros de 3 digitos max, no acepta negativos, '+' es acceptable pero sin repetir (++ no), no pueden haber dos floors o dos ceiling. Tampoco accepta que uno este vacio. 
Numeros solo en rango de 0 - 255. se pueden poner espacios entre los elementos y comas 
pero no aceptara informacion pegada como F45 o F 10,60,70. Requiere dos comas como en el ejemplo. (Aceptable:     F    78   , 60, 90     etc..) 

2. Mapa: no aceptara nada fuera de caracteres 0 1 espacios y
solo una letra, los spaces ' ' son aceptables en el mapa mietras no interactuan 
con el espacio del jugador, el mapa es el ultima informacion, cuando acaba no puede haber nada más aparte de \n. Dentro del mapa no pueden haber \n

3. Enters: he considerado que linea vacias son solo \n (no acepta espacios en esas lineas)

4. Ficheros: mira la extension, que se puedan abrir, que no sean directorios, si hay permisos (tanto .cub como los pngs). Los path de textura no se pueden repetir ni tampoco puede faltar una path. Pueden haber separaciones por los espacios.

Kate (cosas que tengo que arreglar para norminette)
[] files that have more than 5 functions or need changes
-color.c 
-initializer

# Parser

-[X] Check is only one arg
-[X] Argument 1 must be the .cub file

## Elements
-[X] Except for the map, each element can be separated by any number of empty lines
-[X] Except for the map (), each type of element can be separated by one or more spaces
-[X] The map content must always be last and the other elements can be in any order
-[X] If the number of lines is less than 9 -> ERROR
-[X] Check the number of items in the .cub file (must be always 9)

## Textures
-[X] Check files with open if are accesible and not empty;

## Colors
-[X] RGB values must be between 0 and 255

## Map
-[X] Minimum map is 3x3
-[X] If somenthing is no 0 1 N S E W \s -> ERROR
-[X] The map cant be divided by empty lines
-[X] Closings surrounding the player must be 1 always
-[X] Map will keep track of spaces
-[N] Player will be binary 8 | 16 | 32 | 64 == 120
-[X] Check if the player is surrounded by walls
