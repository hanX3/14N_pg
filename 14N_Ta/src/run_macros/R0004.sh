#!/usr/bin/bash

rm ../../../data/R0004/*.root

cd ../

./ana_batch 4 0 158037 &
./ana_batch 4 158037 316074 &
./ana_batch 4 316074 474111 &
./ana_batch 4 474111 632148 &
./ana_batch 4 632148 790185 &
./ana_batch 4 790185 948222 &
