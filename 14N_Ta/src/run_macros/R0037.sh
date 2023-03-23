#!/usr/bin/bash

rm ../../../data/R0037/*.root

cd ../

./ana_batch 37 0 60019 &
./ana_batch 37 60019 120038 &
./ana_batch 37 120038 180057 &
./ana_batch 37 180057 240076 &
./ana_batch 37 240076 300095 &
./ana_batch 37 300095 360114 &
