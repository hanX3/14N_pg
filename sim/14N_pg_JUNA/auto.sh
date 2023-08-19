#!/usr/bin/bash

if [ $# -ne 1 ];then
  echo "need 1 parameter."
  echo "such as: ./auto.sh energy"
  echo "such as: ./auto.sh 7556"
  exit 1
fi

if [ -d b_${1} ];then
  rm -rf b_${1}
fi
mkdir b_${1}
cd b_${1}

cp ../include/Constants.hh ./
case ${1} in
  7556)
    sed -i "s/{0., 0., 0., 0., 0., 0.}/{1., 0., 0., 0., 0., 0.}/g" ../include/Constants.hh
    echo ${1}
    ;;
  6859)
    sed -i "s/{0., 0., 0., 0., 0., 0.}/{0., 1., 0., 0., 0., 0.}/g" ../include/Constants.hh
    echo ${1}
    ;;
  6792)
    sed -i "s/{0., 0., 0., 0., 0., 0.}/{0., 0., 1., 0., 0., 0.}/g" ../include/Constants.hh
    echo ${1}
    ;;
  6172)
    sed -i "s/{0., 0., 0., 0., 0., 0.}/{0., 0., 0., 1., 0., 0.}/g" ../include/Constants.hh
    echo ${1}
    ;;
  5240)
    sed -i "s/{0., 0., 0., 0., 0., 0.}/{0., 0., 0., 0., 1., 0.}/g" ../include/Constants.hh
    echo ${1}
    ;;
  5180)
    sed -i "s/{0., 0., 0., 0., 0., 0.}/{0., 0., 0., 0., 0., 1.}/g" ../include/Constants.hh
    echo ${1}
    ;;  
  *)
    echo "unknown gamma energy"
    exit 1
    ;;
esac

cp ../include/Constants.hh ./Constants.hh.used
cmake ..
make -j6

for num in {1..20};
do
  nohup ./HPGe run2.mac >> ${1}keV.txt &
  nohup ./HPGe run3.mac >> ${1}keV.txt &
  echo ${1}keV.txt
  sleep 5
done

cp Constants.hh ../include/
