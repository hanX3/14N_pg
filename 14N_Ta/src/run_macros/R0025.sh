#!/usr/bin/bash

rm ../../../data/R0025/*.root

cd ../

./ana_batch 25 0 53709 &
./ana_batch 25 53709 107418 &
./ana_batch 25 107418 161127 &
./ana_batch 25 161127 214836 &
./ana_batch 25 214836 268545 &
./ana_batch 25 268545 322254 &
