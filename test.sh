#!/bin/sh

set -v

./matrix_math -h

./matrix_math -inp D -out inp
./matrix_math -add X Y -out add
./matrix_math -sub X Y -out sub
./matrix_math -mul X Y -out mul
./matrix_math -eq X Y -out eq_false
./matrix_math -eq L M -out eq_true
./matrix_math -T A -out trans
./matrix_math -det D -out det
./matrix_math -1 D -out inv
./matrix_math -solve D

./matrix_math -inp A
./matrix_math -add A B
./matrix_math -sub A B
./matrix_math -mul A B
./matrix_math -eq A B
./matrix_math -T A
./matrix_math -1 A
./matrix_math -det A

./matrix_math -det A
./matrix_math -1 A
./matrix_math -det E
./matrix_math -1 E

./matrix_math -not valid
./matrix_math -Trans
./matrix_math -inp bad_file_name
./matrix_math -add A

./matrix_math -inp Destruct

./matrix_math -inp String
