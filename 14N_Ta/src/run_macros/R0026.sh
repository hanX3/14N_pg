#!/usr/bin/bash

rm ../../../data/R0026/*.root

cd ../

./ana_batch 26 0 57813 &
./ana_batch 26 57813 115626 &
./ana_batch 26 115626 173439 &
./ana_batch 26 173439 231252 &
./ana_batch 26 231252 289065 &
./ana_batch 26 289065 346878 &
