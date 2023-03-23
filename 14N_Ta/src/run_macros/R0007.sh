#!/usr/bin/bash

rm ../../../data/R0007/*.root

cd ../

./ana_batch 7 0 155086 &
./ana_batch 7 155086 310172 &
./ana_batch 7 310172 465258 &
./ana_batch 7 465258 620344 &
./ana_batch 7 620344 775430 &
./ana_batch 7 775430 930516 &
