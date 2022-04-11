#!/bin/sh

sudo apt install autoconf automake build-essential cmake libdaxctl-dev \
libndctl-dev libnuma-dev libtbb-dev libtool rapidjson-dev pandoc valgrind

cd ~
git clone https://github.com/pmem/pmdk
cd pmdk
make -j$(nproc)
sudo make install

cd ~
git clone https://github.com/pmem/libpmemobj-cpp
cd libpmemobj-cpp
mkdir build
cd build
cmake ..
make -j$(nproc)
sudo make install