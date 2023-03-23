#!/usr/bin/bash

rm ../../../data/R0032/*.root

cd ../

./ana_batch 32 0 41063 &
./ana_batch 32 41063 82126 &
./ana_batch 32 82126 123189 &
./ana_batch 32 123189 164252 &
./ana_batch 32 164252 205315 &
./ana_batch 32 205315 246378 &
