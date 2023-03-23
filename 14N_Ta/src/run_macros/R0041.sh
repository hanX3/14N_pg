#!/usr/bin/bash

rm ../../../data/R0041/*.root

cd ../

./ana_batch 41 0 59008 &
./ana_batch 41 59008 118016 &
./ana_batch 41 118016 177024 &
./ana_batch 41 177024 236032 &
./ana_batch 41 236032 295040 &
./ana_batch 41 295040 354048 &
