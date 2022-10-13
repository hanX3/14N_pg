#!/usr/bin/bash

rm ../../../data/R0040/*.root

cd ../

./ana_batch 40 0 57607 &
./ana_batch 40 57607 115214 &
./ana_batch 40 115214 172821 &
./ana_batch 40 172821 230428 &
./ana_batch 40 230428 288035 &
./ana_batch 40 288035 345642 &
