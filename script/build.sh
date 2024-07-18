#!/bin/bash

set -eou pipefail

# Get Script Path
SCRIPT=$(readlink -f "$0")
SCRIPT_PATH=$(dirname "$SCRIPT")

cmake -S "$SCRIPT_PATH/../" -B "$SCRIPT_PATH/../build" -Wdev -Werror=dev

cd "$SCRIPT_PATH/../build"
make
cd - > /dev/null
