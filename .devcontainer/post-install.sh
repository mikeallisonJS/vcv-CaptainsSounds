#!/bin/bash
set -e

rm -rf Rack-SDK
wget https://vcvrack.com/downloads/Rack-SDK-2.6.0-lin-x64.zip
unzip Rack-SDK-2.6.0-lin-x64.zip
rm Rack-SDK-2.6.0-lin-x64.zip

# Ensure proper permissions
chmod -R 755 Rack-SDK

# Create dep directory if it doesn't exist
mkdir -p dep

# Initialize git submodules if any
git submodule update --init --recursive

# Run make dep to fetch dependencies
make dep
