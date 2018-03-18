#!/bin/bash

set -e
set -o xtrace

PUBLISH_DIR=$1

[[ -z "$PUBLISH_DIR" ]] && echo "Missing PUBLISH_DIR argument. Stopping.." && exit 1

cd $(dirname $0)/..


echo "Running Documentation generator ..."
doxygen && mv ./docs/html ${PUBLISH_DIR}/docs

echo "Removing old files ..."
rm -fr ./docs

echo "... running Documentation generator done."

