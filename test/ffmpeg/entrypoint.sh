#!/bin/bash

setup() {
    echo "CHUNO-setup"
    export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
    # Configure
    #cmake . -Bbuild

    # Build & install ZoneMindercd
    #make && make install

}

setup

# ===============================================
# Stay in a loop to keep the container running
while :
do
    # perhaps output some stuff here or check apache & mysql are still running
    sleep 2
done
