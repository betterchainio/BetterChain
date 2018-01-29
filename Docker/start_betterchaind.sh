#!/bin/sh
cd /opt/betterchain/bin

if [ -f '/opt/betterchain/bin/data-dir/config.ini' ]; then
    echo
  else
    cp /config.ini /opt/betterchain/bin/data-dir
fi

if [ -f '/opt/betterchain/bin/data-dir/genesis.json' ]; then
    echo
  else
    cp /genesis.json /opt/betterchain/bin/data-dir
fi

if [ -d '/opt/betterchain/bin/data-dir/contracts' ]; then
    echo
  else
    cp -r /contracts /opt/betterchain/bin/data-dir
fi

exec /opt/betterchain/bin/betterchaind $@
