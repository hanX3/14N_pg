#!/usr/bin/bash

rm ../../../data/R0011/*.root

cd ../

./ana_batch 11 0 155519 &
./ana_batch 11 155519 311038 &
./ana_batch 11 311038 466557 &
./ana_batch 11 466557 622076 &
./ana_batch 11 622076 777595 &
./ana_batch 11 777595 933114 &
