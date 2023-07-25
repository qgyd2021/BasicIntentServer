#!/usr/bin/env bash

mkdir cmake-build-debug/
cmake -B cmake-build-debug/

cmake --build ./cmake-build-debug --target BasicIntentServer -j "$(grep -c ^processor /proc/cpuinfo)"

#./cmake-build-debug/BasicIntentServer

