#!/bin/bash
threshold=$1
main_surf=$2
ref_surf=$3
base_name=$4
iterations=$5

function improver {
  clean
  # sudo make build-moct
  i=0
  while [ "$i" -le "$iterations" ]
  do
    prev_i=$(($i-1))
    out_name=${base_name}_$i

    if (( $i == 0 )); then
      # ./mesher_roi -d $main_surf -s 7 -u $out_name -m -v -t $threshold &> ./$out_name.log
      ./mesher_roi -d $main_surf -s 8 -r $ref_surf 10 -u $out_name -m -v -t $threshold &> ./${base_name}_$i.log
    else
      ./mesher_roi -d $main_surf -c ./${base_name}_$prev_i.oct -l ./${base_name}_$prev_i.ref -u $out_name -m -v -t $threshold &> ./$out_name.log
    fi
    
    eval_improver $out_name $i
    i=$(($i+1))
  done
  echo "Finished, number of iterations exceeded."
  ref_name=./$out_name.ref
  lo=$(wc -l < $ref_name)
  echo "Octants to improve: $lo"
}

function eval_improver {
  ref_name=./$1.ref
  if [ ! -f "$ref_name" ]; then
    echo "No more Octants to improve in iteration $2."
    moveExport $base_name
    exit 0
  else 
    lo=$(wc -l < $ref_name)
    echo "Octants to improve in iteration $2: $lo"
  fi
}

function clean {
  sudo rm -rf ./*.{oct,ref,log,vtk,m3d,histo,map}
}

function moveExport {
  mkdir ./data_analysis/$1
  mv ./*.{oct,ref,log,vtk,m3d,histo,map} ./data_analysis/$1
}

if [ "$threshold" = "" ]; then
  echo "Threshold not provided"
fi
if [ "$main_surf" = "" ]; then
  echo "Main surface not provided"
fi
if [ "$ref_surf" = "" ]; then
  echo "Reference surface not provided"
fi
if [ "$base_name" = "" ]; then
  echo "Base name not provided"
fi
if [ "$iterations" = "" ]; then
  echo "Number of iterations not provided"
fi

if [ "$threshold" = "" ] || [ "$main_surf" = "" ] || [ "$ref_surf" = "" ] || [ "$base_name" = "" ] || [ "$iterations" = "" ]; then
  exit 0
else
  echo "Threshold: $threshold"
  echo "Main surface: $main_surf"
  echo "Reference surface: $ref_surf"
  echo "Base name: $base_name"
  echo "Number of iterations: $iterations"
  improver
fi
