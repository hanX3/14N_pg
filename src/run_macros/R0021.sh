#!/usr/bin/bash

rm ../../../data/R0021/*.root

cd ../

./ana_batch 21 0 56269 &
./ana_batch 21 56269 112538 &
./ana_batch 21 112538 168807 &
./ana_batch 21 168807 225076 &
./ana_batch 21 225076 281345 &
./ana_batch 21 281345 337614 &
