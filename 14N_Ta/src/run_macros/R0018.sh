#!/usr/bin/bash

rm ../../../data/R0018/*.root

cd ../

./ana_batch 18 0 55564 &
./ana_batch 18 55564 111128 &
./ana_batch 18 111128 166692 &
./ana_batch 18 166692 222256 &
./ana_batch 18 222256 277820 &
./ana_batch 18 277820 333384 &
