#!/bin/sh

set -eu

export RACK_DIR=${GITHUB_WORKSPACE}/Rack-SDK
export RACK_USER_DIR=${GITHUB_WORKSPACE}

git submodule update --init --recursive

curl -L https://vcvrack.com/downloads/Rack-SDK-${RACK_SDK_VERSION}.zip -o rack-sdk.zip
unzip -o rack-sdk.zip
rm rack-sdk.zip

build_arch() {
  ARCH_NAME=$1
  CC_BIN=$2
  CXX_BIN=$3
  mkdir -p dist
  export CC=$CC_BIN
  export CXX=$CXX_BIN
  make clean
  make dep
  make dist
  mkdir -p build_${ARCH_NAME}
  # Extract the produced zip into a per-arch directory
  unzip -q -o dist/*.zip -d build_${ARCH_NAME}
  # Clean out dist for the next arch build to avoid ambiguity
  rm -f dist/*.zip
}

# Build x86_64 and arm64 variants
build_arch x64 o64-clang o64-clang++
build_arch arm64 oa64-clang oa64-clang++

# Determine plugin slug and version
PLUGIN_SLUG=$(jq -r .slug plugin.json)
PLUGIN_VERSION=$(jq -r .version plugin.json)

PLUGIN_DIR_X64="build_x64/${PLUGIN_SLUG}"
PLUGIN_DIR_ARM64="build_arm64/${PLUGIN_SLUG}"

# Locate lipo
if command -v lipo >/dev/null 2>&1; then
  LIPO=lipo
elif command -v x86_64-apple-darwin20-lipo >/dev/null 2>&1; then
  LIPO=x86_64-apple-darwin20-lipo
else
  # Fallback: pick the first *-lipo found in osxcross toolchain
  LIPO=$(find /opt/osxcross/target/bin -type f -name "*-lipo" | head -n1)
fi

mkdir -p combine/${PLUGIN_SLUG}
rsync -a --delete ${PLUGIN_DIR_X64}/ combine/${PLUGIN_SLUG}/

# Merge dylibs into a universal binary
${LIPO} -create -output combine/${PLUGIN_SLUG}/plugin.dylib \
  ${PLUGIN_DIR_X64}/plugin.dylib \
  ${PLUGIN_DIR_ARM64}/plugin.dylib

# Repack into dist
mkdir -p dist
cd combine
zip -q -9 -r "../dist/${PLUGIN_SLUG}-${PLUGIN_VERSION}.zip" "./${PLUGIN_SLUG}"
cd ..
