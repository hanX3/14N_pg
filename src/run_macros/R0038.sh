#!/usr/bin/bash

rm ../../../data/R0038/*.root

cd ../

./ana_batch 38 0 45082 &
./ana_batch 38 45082 90164 &
./ana_batch 38 90164 135246 &
./ana_batch 38 135246 180328 &
./ana_batch 38 180328 225410 &
./ana_batch 38 225410 270492 &
