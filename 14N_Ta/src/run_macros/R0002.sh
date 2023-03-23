#!/usr/bin/bash

rm ../../../data/R0002/*.root

cd ../

./ana_batch 2 0 176554 &
./ana_batch 2 176554 353108 &
./ana_batch 2 353108 529662 &
./ana_batch 2 529662 706216 &
./ana_batch 2 706216 882770 &
./ana_batch 2 882770 1059324 &
