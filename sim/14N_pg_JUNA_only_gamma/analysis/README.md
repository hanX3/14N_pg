#

## area.cpp & fit.cpp have not been accepted at last.
area.cpp --> get area from rootfile, and wrtie this area into area_*.txt file; for each gamma energy, we get a curve of entries and area
fit.cpp  --> using fit method to get the entries according to the experimental area of gamma-ray.

## tr2hist.cpp 
1. change root filename into tr_*keV_*.root and move rootfile into analysis directory
2. run tr2hist in the root terminal.
  `root -l`
  `.L tr2hist.cpp; `
  `tr2hist("50M", 6126, 2.5)`
  `tr2hist("100M", 6126, 2.5)`