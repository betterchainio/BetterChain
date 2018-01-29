#!/bin/bash

# Usage:
# Go into cmd loop: sudo ./betterchainc.sh
# Run single cmd:  sudo ./betterchainc.sh <betterchainc paramers>

PREFIX="docker exec docker_betterchaind_1 betterchainc"
if [ -z $1 ] ; then
  while :
  do
    read -e -p "betterchainc " cmd
    history -s "$cmd"
    $PREFIX $cmd
  done
else
  $PREFIX $@
fi
