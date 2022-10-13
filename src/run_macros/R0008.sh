#!/usr/bin/bash

rm ../../../data/R0008/*.root

cd ../

./ana_batch 8 0 169843 &
./ana_batch 8 169843 339686 &
./ana_batch 8 339686 509529 &
./ana_batch 8 509529 679372 &
./ana_batch 8 679372 849215 &
./ana_batch 8 849215 1019058 &
