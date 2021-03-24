#!/bin/bash

EXE="./bin/main"

# boost library path for the dynamically loaded boost libraries, local or from project
#export LD_LIBRARY_PATH=./lib
export LD_LIBRARY_PATH=${HOME}/Projects/boost_1_75_0/stage/lib/


# validate if exe can be ran
function validate()
{
  # check if the executable exists
  if [ ! -f "$EXE" ]; then
    echo "Missing $EXE, run make to build."
    exit 1
  fi

  # check for missing libraries
  local missing=()
  while read -r line; do
    if [[ "$line" =~ " not found" ]]; then
      missing+=("$line")
    fi
  done < <( ldd "$EXE" && printf '\0' )

  local len=${#missing[@]}
  if [ $len -gt 0 ]; then
    echo "Missing libraries..."
    echo "$missing"
    echo "Check path to boost libraries."
    exit 1
  fi
}

validate

echo "Execute $EXE..."
echo ""

# use the email text file as the source for regex parsing
./bin/main
