#!/usr/bin/bash

rm ../../../data/R0013/*.root

cd ../

./ana_batch 13 0 170502 &
./ana_batch 13 170502 341004 &
./ana_batch 13 341004 511506 &
./ana_batch 13 511506 682008 &
./ana_batch 13 682008 852510 &
./ana_batch 13 852510 1023012 &
