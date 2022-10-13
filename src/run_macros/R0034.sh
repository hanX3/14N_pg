#!/usr/bin/bash

rm ../../../data/R0034/*.root

cd ../

./ana_batch 34 0 77137 &
./ana_batch 34 77137 154274 &
./ana_batch 34 154274 231411 &
./ana_batch 34 231411 308548 &
./ana_batch 34 308548 385685 &
./ana_batch 34 385685 462822 &
