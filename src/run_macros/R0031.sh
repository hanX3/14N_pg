#!/usr/bin/bash

rm ../../../data/R0031/*.root

cd ../

./ana_batch 31 0 90159 &
./ana_batch 31 90159 180318 &
./ana_batch 31 180318 270477 &
./ana_batch 31 270477 360636 &
./ana_batch 31 360636 450795 &
./ana_batch 31 450795 540954 &
