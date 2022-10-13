#!/usr/bin/bash

rm ../../../data/R0029/*.root

cd ../

./ana_batch 29 0 56308 &
./ana_batch 29 56308 112616 &
./ana_batch 29 112616 168924 &
./ana_batch 29 168924 225232 &
./ana_batch 29 225232 281540 &
./ana_batch 29 281540 337848 &
