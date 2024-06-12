#!/bin/bash
sudo rm -rf ./c_5r7_*
sudo make build-moct
threshold=(0.03)
for i in {0..5}
do
  new=$(($i-1))
  echo "==== ITERACION $i ===="
  if (( $i == 0 )); then
    ./mesher_roi -d ./data/cortex.mdl -s 5 -r ./data/cortex_surf_roi.mdl 7 -u c_5r7_$i -m -v -t $threshold &> ./c_5r7_$i.log
  else
    ./mesher_roi -d ./data/cortex.mdl -c ./c_5r7_$new.oct -l ./c_5r7_$new.ref -u c_5r7_$i -m -v -t $threshold &> ./c_5r7_$i.log
  fi
done