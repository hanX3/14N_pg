#!/usr/bin/bash

rm ../../../data/R0016/*.root

cd ../

./ana_batch 16 0 147956 &
./ana_batch 16 147956 295912 &
./ana_batch 16 295912 443868 &
./ana_batch 16 443868 591824 &
./ana_batch 16 591824 739780 &
./ana_batch 16 739780 887736 &
