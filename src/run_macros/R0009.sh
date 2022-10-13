#!/usr/bin/bash

rm ../../../data/R0009/*.root

cd ../

./ana_batch 9 0 179815 &
./ana_batch 9 179815 359630 &
./ana_batch 9 359630 539445 &
./ana_batch 9 539445 719260 &
./ana_batch 9 719260 899075 &
./ana_batch 9 899075 1078890 &
