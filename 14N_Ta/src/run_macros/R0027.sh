#!/usr/bin/bash

rm ../../../data/R0027/*.root

cd ../

./ana_batch 27 0 34411 &
./ana_batch 27 34411 68822 &
./ana_batch 27 68822 103233 &
./ana_batch 27 103233 137644 &
./ana_batch 27 137644 172055 &
./ana_batch 27 172055 206466 &
