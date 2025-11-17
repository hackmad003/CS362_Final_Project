#!/bin/bash

# Exit the script whenever a non-zero exit status is received
set -e

# Define parameters
LIB="$1"

# Validate arguments
if [ "$#" -lt 1 ]; then
	echo "install.sh: error: No library name was specified"
	echo "install.sh: usage: install.sh <name>"
	exit 1
fi


# Define local variables
SRC_DIR="$(dirname "$0")/$LIB"
ARDUINO_DIR="$HOME/Arduino/libraries"
DEST="$ARDUINO_DIR/$LIB"

# Remove old library
if [ -d "$DEST" ]; then
    rm -rf "$DEST"
fi

# Copy the library
cp -r "$SRC_DIR" "$DEST"

echo "Installed $LIB to $ARDUINO_DIR"

