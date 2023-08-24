#!/usr/bin/bash

if [ $# -ne 1 ];then
  echo "need 1 parameter."
  echo "such as: ./auto.sh distance[mm]"
  echo "such as: ./auto.sh"
  exit 1
fi

if [ -d b_${1}mm ];then
  rm -rf b_${1}mm
fi
mkdir b_${1}mm
cd b_${1}mm

cp ../include/Constants.hh ./
old="TargetGeDis = 140"
new="TargetGeDis = "${1}

echo ${old}
echo ${new}
sed -i "s/${old}/${new}/g" ../include/Constants.hh

cp ../include/Constants.hh ./Constants.hh.used
cmake ..
make -j6
cp Constants.hh ../include/

nohup ./HPGe run2.mac >> dis${1}.txt &
echo dis${1}.txt

#