#!/usr/bin/bash

rm ../../../data/R0030/*.root

cd ../

./ana_batch 30 0 58603 &
./ana_batch 30 58603 117206 &
./ana_batch 30 117206 175809 &
./ana_batch 30 175809 234412 &
./ana_batch 30 234412 293015 &
./ana_batch 30 293015 351618 &
