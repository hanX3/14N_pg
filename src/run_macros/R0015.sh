#!/usr/bin/bash

rm ../../../data/R0015/*.root

cd ../

./ana_batch 15 0 36391 &
./ana_batch 15 36391 72782 &
./ana_batch 15 72782 109173 &
./ana_batch 15 109173 145564 &
./ana_batch 15 145564 181955 &
./ana_batch 15 181955 218346 &
