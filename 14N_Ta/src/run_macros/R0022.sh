#!/usr/bin/bash

rm ../../../data/R0022/*.root

cd ../

./ana_batch 22 0 55862 &
./ana_batch 22 55862 111724 &
./ana_batch 22 111724 167586 &
./ana_batch 22 167586 223448 &
./ana_batch 22 223448 279310 &
./ana_batch 22 279310 335172 &
