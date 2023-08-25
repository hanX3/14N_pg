#

scp -r 14N_pg_JUNA_eff hanX@222.194.16.234:/media/DATA4T4/hanX/14N_pg/git/sim/

get HPGe efficiency curve by simulation

* tr2hist.cpp --> add resolusion info to raw rootfile, generate new root histogram and save to dis\* directory;
* rename.sh --> rename raw rootfile, new rootfile name dis_\*mm_gamma_\*keV_10000k.root;
* batch.cpp --> batch analysis, and get histogram;


* filename.txt --> the simulation data of single gamma-ray from 1500 keV to 12500 keV;
* area.cpp     --> get area from simulation data file, write area_energy.txt/area3_energy.txt 4 coulomn including energy & area counts & total counts & total emmission, and the same with the area.cpp file in 14N_Ti/branch_ratio directory; 
* fit.cpp      --> fit full-energy efficiency curve, fit full-energy/total efficiency curve, get efficiency of gamma-ray considering summing effect or not, write the result file y1y2.txt with 3 coulomn include gamma-ray energy & efficiency do not considering summing effect & efficiency considering summing effect;