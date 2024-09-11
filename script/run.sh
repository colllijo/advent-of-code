#!/bin/bash

set -eou pipefail

# Get Script Path
SCRIPT=$(readlink -f "$0")
SCRIPT_PATH=$(dirname "$SCRIPT")

if bash "$SCRIPT_PATH/build.sh" > /dev/null; then
  time "$SCRIPT_PATH/../build/coll-aoc" "$@"
fi
