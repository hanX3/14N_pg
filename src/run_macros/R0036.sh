#!/usr/bin/bash

rm ../../../data/R0036/*.root

cd ../

./ana_batch 36 0 59981 &
./ana_batch 36 59981 119962 &
./ana_batch 36 119962 179943 &
./ana_batch 36 179943 239924 &
./ana_batch 36 239924 299905 &
./ana_batch 36 299905 359886 &
