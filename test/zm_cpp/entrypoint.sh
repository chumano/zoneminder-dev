#!/bin/bash

setup() {
    echo "CHUNO-setup"
    
    cd /src
    # Configure
    cmake .

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
