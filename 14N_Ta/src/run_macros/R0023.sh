#!/usr/bin/bash

rm ../../../data/R0023/*.root

cd ../

./ana_batch 23 0 55815 &
./ana_batch 23 55815 111630 &
./ana_batch 23 111630 167445 &
./ana_batch 23 167445 223260 &
./ana_batch 23 223260 279075 &
./ana_batch 23 279075 334890 &
