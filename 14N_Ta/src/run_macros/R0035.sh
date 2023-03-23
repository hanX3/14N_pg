#!/usr/bin/bash

rm ../../../data/R0035/*.root

cd ../

./ana_batch 35 0 60657 &
./ana_batch 35 60657 121314 &
./ana_batch 35 121314 181971 &
./ana_batch 35 181971 242628 &
./ana_batch 35 242628 303285 &
./ana_batch 35 303285 363942 &
