## scp -r analysis/ hanX@222.194.16.234:/media/DATA4T4/hanX/14N_pg/git/sim/14N_pg_JUNA/
## scp hanX@222.194.16.234:/media/DATA4T4/hanX/14N_pg/git/sim/14N_pg_JUNA/analysis/\*.root ./

## scp hanX@222.194.16.234:/media/DATA4T4/hanX/14N_pg/git/sim/14N_pg_JUNA/data/tr*.root ./

* hadd.sh --> used for add root files into one;
* tr2hist.cpp --> convert tree structure into histogram. This is a main code;
* batch.cpp --> run all of rootfiles in the cpp code.
  `root -l`
  `.L batch.cpp;`
  `batch(2.5); // 2.5 denotes sigma value`