#!/bin/sh

if [ $# -eq 0 ]; then
  script_name=`basename "$0"`
  echo "Usage: $script_name searchfor [... searchfor]"
  echo "(You didn't tell me what you want to search for.)"
  exit 1
fi

original_args="$@"

datafile="mydata.txt"
temp_results="temp_results.$$" 
filtered_temp="filtered.$$"   

cp "$datafile" "$temp_results" 

for term_to_search in $original_args
do
  grep -i "$term_to_search" "$temp_results" > "$filtered_temp"

  if [ ! -s "$filtered_temp" ]; then
    rm -f "$temp_results" "$filtered_temp" 
    exit 0 
  fi

  mv "$filtered_temp" "$temp_results"
done

if [ -s "$temp_results" ]; then
  awk -f display.awk "$temp_results"
fi

rm -f "$temp_results" 

exit 0