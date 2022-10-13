#!/usr/bin/bash

rm ../../../data/R0010/*.root

cd ../

./ana_batch 10 0 160822 &
./ana_batch 10 160822 321644 &
./ana_batch 10 321644 482466 &
./ana_batch 10 482466 643288 &
./ana_batch 10 643288 804110 &
./ana_batch 10 804110 964932 &
