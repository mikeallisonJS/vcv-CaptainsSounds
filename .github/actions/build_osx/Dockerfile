FROM debian:bookworm

LABEL "com.github.actions.name"="VCVRackPluginBuilder-OSX"
LABEL "com.github.actions.description"="Builds a VCV Rack plugin for macOS using osxcross"
LABEL "com.github.actions.icon"="headphones"
LABEL "com.github.actions.color"="purple"

LABEL "repository"="TBD"
LABEL "homepage"="TBD"
LABEL "maintainer"="dewb"

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
      automake \
      bison \
      curl \
      file \
      flex \
      git \
      libtool \
      pkg-config \
      python3 \
      texinfo \
      wget \
      zlib1g-dev \
      build-essential \
      cmake \
      make \
      tar \
      unzip \
      zip \
      libgl1-mesa-dev \
      libglu1-mesa-dev \
      jq \
      rsync \
      ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Install osxcross (modern commit and SDK)
ENV OSXCROSS_SDK_VERSION 11.3
RUN mkdir -p /opt && \
    cd /opt && \
    git clone https://github.com/tpoechtrager/osxcross.git && \
    cd osxcross && \
    sed -i -e 's|-march=native||g' ./build_clang.sh ./wrapper/build.sh && \
    ./tools/get_dependencies.sh && \
    curl -L -o ./tarballs/MacOSX${OSXCROSS_SDK_VERSION}.sdk.tar.xz \
      https://github.com/joseluisq/macosx-sdks/releases/download/${OSXCROSS_SDK_VERSION}/MacOSX${OSXCROSS_SDK_VERSION}.sdk.tar.xz && \
    yes | PORTABLE=true ./build.sh && \
    ./build_compiler_rt.sh

ENV PATH $PATH:/opt/osxcross/target/bin

ADD entrypoint.sh /entrypoint.sh
RUN chmod a+x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
