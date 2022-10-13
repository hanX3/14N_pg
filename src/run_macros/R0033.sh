#!/usr/bin/bash

rm ../../../data/R0033/*.root

cd ../

./ana_batch 33 0 60966 &
./ana_batch 33 60966 121932 &
./ana_batch 33 121932 182898 &
./ana_batch 33 182898 243864 &
./ana_batch 33 243864 304830 &
./ana_batch 33 304830 365796 &
