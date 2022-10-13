#!/usr/bin/bash

rm ../../../data/R0017/*.root

cd ../

./ana_batch 17 0 57353 &
./ana_batch 17 57353 114706 &
./ana_batch 17 114706 172059 &
./ana_batch 17 172059 229412 &
./ana_batch 17 229412 286765 &
./ana_batch 17 286765 344118 &
