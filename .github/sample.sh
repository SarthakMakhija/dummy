#!/bin/sh

sudo rm -rf /usr/local/lib/libpmem*

ls -ltr /usr/local/lib/libpmem*

sudo apt install autoconf automake build-essential libdaxctl-dev \
libndctl-dev libnuma-dev libtbb-dev libtool rapidjson-dev pandoc valgrind

#libpmemobj-cpp-dev

cd ~
git clone https://github.com/pmem/pmdk
cd pmdk
make -j$(nproc)
sudo make install

