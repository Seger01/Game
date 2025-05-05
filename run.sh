#!/bin/bash

mkdir code/build

cd code/build || exit 1

cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 .. -DCMAKE_BUILD_TYPE=Release
if [ $? -ne 0 ]; then
    echo "CMake configuration failed."
    exit 1
fi

make -j16
if [ $? -ne 0 ]; then
    echo "Build failed."
    exit 1
fi

cd .. || exit 1

./build/bin/BulletBravo
