# Parser

-[X] Check is only one arg
-[X] Argument 1 must be the .cub file

## Elements
-[ ] Except for the map, each element can be separated by any number of empty lines
-[ ] Except for the map (), each type of element can be separated by one or more spaces
-[X] The map content must always be last and the other elements can be in any order
-[X] If the number of lines is less than 9 -> ERROR
-[ ] Check the number of items in the .cub file (must be always 9)

## Textures
-[ ] Check files with open if are accesible and not empty;

## Colors
-[ ] RGB values must be between 0 and 255

## Map
-[X] Minimum map is 3x3
-[X] If somenthing is no 0 1 N S E W \s -> ERROR
-[X] The map cant be divided by empty lines
-[X] Closings surrounding the player must be 1 always
-[X] Map will keep track of spaces
-[ ] Player will be binary 8 | 16 | 32 | 64 == 120
-[X] Check if the player is surrounded by walls
