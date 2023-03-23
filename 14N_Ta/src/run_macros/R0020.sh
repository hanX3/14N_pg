#!/usr/bin/bash

rm ../../../data/R0020/*.root

cd ../

./ana_batch 20 0 57144 &
./ana_batch 20 57144 114288 &
./ana_batch 20 114288 171432 &
./ana_batch 20 171432 228576 &
./ana_batch 20 228576 285720 &
./ana_batch 20 285720 342864 &
