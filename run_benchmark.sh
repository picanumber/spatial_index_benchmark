#!/bin/sh
################################################################################
# Script running spatial_index_benchmark programs
# https://github.com/mloskot/spatial_index_benchmark
################################################################################
# Copyright (C) 2013 Mateusz Loskot <mateusz@loskot.net>
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)
################################################################################

if [[ ! -d $1 ]]; then
    echo "Cannot find '$1' build directory"
    exit 1
fi

BDIR="$1"
#
# Benchmark iterative loading (takes long time, skipped on Travis CI)
#
if [[ "$TRAVIS" != "true" ]] ; then
for variant in linear quadratic rstar
do
    for benchmark in `find $BDIR -type f -name "*${variant}" -executable | sort`
    do
        ${benchmark} > ${benchmark}.log
    done;
done;
fi

#
# Benchmark bulk loading
#
for variant in linear quadratic rstar
do
    for benchmark in `find $BDIR -type f -name "*${variant}_blk" -executable | sort`
    do
        ${benchmark} > ${benchmark}.log
    done;
done;