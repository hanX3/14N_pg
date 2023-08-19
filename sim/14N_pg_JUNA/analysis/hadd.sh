#!/usr/bin/bash

energy=(7556 6859 6792 6172 5240 5180)

for e in "${energy[@]}";
do
  hadd ../data/tr_${e}keV_50M.root ../data/*${e}keV_5000k.root
  hadd ../data/tr_${e}keV_100M.root ../data/*${e}keV_10000k.root
done

