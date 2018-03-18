#!/bin/bash

set -e
set -o xtrace

PUBLISH_DIR=$1

[[ -z "$PUBLISH_DIR" ]] && echo "Missing PUBLISH_DIR argument. Stopping.." && exit 1

cd $(dirname $0)/..


echo "Running Code Metrics report generator ..."

INPUT_TXT=`mktemp`
REPORT_XML_OUTPUT=cccc_report.xml
REPORT_HTML_OUTPUT=cccc_report.html
OUTPUT_DIR=${PUBLISH_DIR}/metrics

echo "Collecting input source files ..."
for INPUT_DIR in ./src ./include;
do
  find ${INPUT_DIR} -name "*.c" \
                -or -name "*.cc" \
                -or -name "*.cpp" \
                -or -name "*.h" \
                -or -name "*.hpp" >> ${INPUT_TXT}
done

echo "Listing collected files ..."
cat ${INPUT_TXT}

echo "Making output directory ..."
mkdir -p ${OUTPUT_DIR}

echo "Running cccc ..."
cat ${INPUT_TXT} | xargs cccc --outdir="${OUTPUT_DIR}" --xml_outfile=${OUTPUT_DIR}/${REPORT_XML_OUTPUT} --html_outfile=${OUTPUT_DIR}/${REPORT_HTML_OUTPUT}

echo "Linking final report ..."
ln -fs ${OUTPUT_DIR}/${REPORT_HTML_OUTPUT} ${OUTPUT_DIR}/index.html

echo "Removing old files ..."
rm ${INPUT_TXT}

echo "... running Code Metrics Report generator done."

