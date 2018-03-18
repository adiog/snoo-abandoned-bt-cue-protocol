#!/bin/bash

set -e
set -o xtrace

PUBLISH_DIR=$1

[[ -z "$PUBLISH_DIR" ]] && echo "Missing PUBLISH_DIR argument. Stopping.." && exit 1

cd $(dirname $0)/..


echo "Running Coverage report generator ..."

echo "Making working directory ..."
mkdir -p ./build-coverage && cd ./build-coverage

echo "Building and running tests ..."
cmake -DENABLE_PROTOCOL_TESTING=ON .. \
  && make \
  && make test

echo "Running gcov ..."
find . -name "*.gc*" -exec gcov {} \;

echo "Running lcov ..."
lcov -c -d . -o cov.info

echo "Generating HTML report ..."
genhtml cov.info --output-directory ${PUBLISH_DIR}/coverage

echo "Removing old files ..."
rm -fr ./build-coverage

echo "... running Coverage report generator done."

