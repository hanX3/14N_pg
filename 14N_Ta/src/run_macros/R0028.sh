#!/usr/bin/bash

rm ../../../data/R0028/*.root

cd ../

./ana_batch 28 0 50904 &
./ana_batch 28 50904 101808 &
./ana_batch 28 101808 152712 &
./ana_batch 28 152712 203616 &
./ana_batch 28 203616 254520 &
./ana_batch 28 254520 305424 &
