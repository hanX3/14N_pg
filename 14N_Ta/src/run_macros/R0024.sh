#!/usr/bin/bash

rm ../../../data/R0024/*.root

cd ../

./ana_batch 24 0 57642 &
./ana_batch 24 57642 115284 &
./ana_batch 24 115284 172926 &
./ana_batch 24 172926 230568 &
./ana_batch 24 230568 288210 &
./ana_batch 24 288210 345852 &
