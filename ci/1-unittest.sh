#!/bin/bash

set -e
set -o xtrace

PUBLISH_DIR=$1

[[ -z "$PUBLISH_DIR" ]] && echo "Missing PUBLISH_DIR argument. Stopping.." && exit 1

cd $(dirname $0)/..


echo "Running Unit Tests ..."

echo "Making working directory ..."
mkdir -p ./build-unittest && cd ./build-unittest

echo "Building and running tests ..."
cmake -DENABLE_PROTOCOL_TESTING=ON .. \
  && make \
  && GTEST_OUTPUT="xml:${PUBLISH_DIR}/unittest.xml" make test

echo "Removing old files ..."
rm -fr ./build-unittest

echo "... running Unit Tests done."

