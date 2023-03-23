#!/usr/bin/bash

rm ../../../data/R0019/*.root

cd ../

./ana_batch 19 0 56963 &
./ana_batch 19 56963 113926 &
./ana_batch 19 113926 170889 &
./ana_batch 19 170889 227852 &
./ana_batch 19 227852 284815 &
./ana_batch 19 284815 341778 &
