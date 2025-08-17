FROM debian:bookworm

LABEL "com.github.actions.name"="VCVRackPluginBuilder-Windows"
LABEL "com.github.actions.description"="Builds a VCV Rack plugin for Windows"
LABEL "com.github.actions.icon"="headphones"
LABEL "com.github.actions.color"="purple"

LABEL "repository"="TBD"
LABEL "homepage"="TBD"
LABEL "maintainer"="dewb"

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
      build-essential \
      cmake \
      curl \
      gcc \
      g++ \
      git \
      make \
      tar \
      unzip \
      zip \
      libgl1-mesa-dev \
      libglu1-mesa-dev \
      jq \
      g++-mingw-w64-x86-64 \
      wget \
      ca-certificates && \
    rm -rf /var/lib/apt/lists/*

ADD entrypoint.sh /entrypoint.sh
RUN chmod a+x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
