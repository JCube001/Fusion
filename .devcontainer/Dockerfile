FROM mcr.microsoft.com/devcontainers/base:ubuntu26.04

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    catch2 \
    g++ \
    gcc \
    make \
    pkgconf \
    && rm -rf /var/lib/apt/lists/*
