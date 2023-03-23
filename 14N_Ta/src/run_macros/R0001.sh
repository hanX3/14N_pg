#!/usr/bin/bash

rm ../../../data/R0001/*.root

cd ../

./ana_batch 1 0 222228 &
./ana_batch 1 222228 444456 &
./ana_batch 1 444456 666684 &
./ana_batch 1 666684 888912 &
./ana_batch 1 888912 1111140 &
./ana_batch 1 1111140 1333368 &
