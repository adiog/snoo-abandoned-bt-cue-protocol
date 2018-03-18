#!/bin/bash

PUBLISH_DIR=$(realpath $1)

[[ -z "$PUBLISH_DIR" ]] && echo "Missing PUBLISH_DIR argument. Stopping.." && exit 1

mkdir -p ${PUBLISH_DIR}

CI_DIR=$(dirname $0)

${CI_DIR}/1-unittest.sh ${PUBLISH_DIR}
${CI_DIR}/2-doxygen.sh ${PUBLISH_DIR}
${CI_DIR}/3-metrics.sh ${PUBLISH_DIR}
${CI_DIR}/4-coverage.sh ${PUBLISH_DIR}

