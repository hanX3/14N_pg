#!/usr/bin/bash

rm ../../../data/R0039/*.root

cd ../

./ana_batch 39 0 67424 &
./ana_batch 39 67424 134848 &
./ana_batch 39 134848 202272 &
./ana_batch 39 202272 269696 &
./ana_batch 39 269696 337120 &
./ana_batch 39 337120 404544 &
