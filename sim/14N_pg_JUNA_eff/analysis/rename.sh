#!/usr/bin/bash

for (( i=20; i<=300; i+=20 )); 
do
  filepath="../b_"${i}"mm/data/"
  # echo ${filepath}
  if [ -d ${filepath} ]; then
    echo "analysis "${filepath}
    for file in "${filepath}"*; 
    do
      # echo ${file}
      file1="${file#*_}"
      file2="${file1#*_}"
      file3="${file2#*_}"

      echo ${filepath}"dis_"${i}"mm_"${file3}
      mv ${file} ${filepath}"dis_"${i}"mm_"${file3}
    done
  fi
done
