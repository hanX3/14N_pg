#!/usr/bin/bash

rm ../../../data/R0014/*.root

cd ../

./ana_batch 14 0 104954 &
./ana_batch 14 104954 209908 &
./ana_batch 14 209908 314862 &
./ana_batch 14 314862 419816 &
./ana_batch 14 419816 524770 &
./ana_batch 14 524770 629724 &
