#!/bin/bash
# Builds and runs spatial_index_benchmark
source ./bin/ci/common.sh
mkdir -p _build
cd _build
echo "Calling cmake -DBOOST_PREFIX=${BOOST_PREFIX}"
cmake \
	-DCMAKE_VERBOSE_MAKEFILE=ON \
    -DBOOST_ROOT=${BOOST_PREFIX} \
	..
#cmake --build .
make -j ${NUMTHREADS}