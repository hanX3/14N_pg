#!/usr/bin/bash

rm ../../../data/R0042/*.root

cd ../

./ana_batch 42 0 57077 &
./ana_batch 42 57077 114154 &
./ana_batch 42 114154 171231 &
./ana_batch 42 171231 228308 &
./ana_batch 42 228308 285385 &
./ana_batch 42 285385 342462 &
