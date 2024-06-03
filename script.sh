#!/bin/bash
sudo make build-moct
echo "==== REFINAMIENTO INICIAL ===="
./mesher_roi -d ./data/cortex.mdl -s 5 -r ./data/cortex_surf_roi.mdl 7 -u c_5r7_0 -m -v -t 0.0
for i in {0..20}
do
  echo "==== ITERACION $i ===="
  new=$(($i+1))
  echo "var : $new"
  ./mesher_roi -d ./data/cortex.mdl -c ./c_5r7_$i.oct -l ./c_5r7_$i.ref -u c_5r7_$new -m -v -t 0.0
done