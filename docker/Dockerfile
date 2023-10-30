FROM ubuntu:18.04

# ENV DEBIAN_FRONTEND=noninteractive

ENV TZ=Asia/Shanghai

SHELL ["/bin/bash", "-c"]

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update
RUN apt-get install software-properties-common -y

RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt-get install -y wget build-essential software-properties-common git \
    curl g++-10 libbz2-dev libcurl4-openssl-dev libgflags-dev libsnappy-dev zlib1g-dev libboost-thread-dev libboost-filesystem-dev \
    libssl-dev python libtbb-dev ccache 

ENV CXX /usr/bin/g++-10
ENV CC /usr/bin/gcc-10
RUN mkdir -p /ax-install/cmake
RUN mkdir -p /ax-install/aws-install

WORKDIR /ax-install
RUN curl -JLO https://cmake.org/files/v3.28/cmake-3.28.0-rc1-linux-x86_64.tar.gz
WORKDIR /usr/local
RUN tar xfz /ax-install/cmake-3.28.0-rc1-linux-x86_64.tar.gz --strip-components=1

WORKDIR /ax-install
RUN git clone --recurse-submodules https://github.com/aws/aws-sdk-cpp.git
WORKDIR /ax-install/aws-install
RUN cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTING=OFF '-DBUILD_ONLY=kinesis;core;s3;transfer' ../aws-sdk-cpp/
RUN make -j 8 && make install

WORKDIR /ax-install
ENV LIBRDKAFKA_VERSION=2.2.0
RUN wget https://github.com/edenhill/librdkafka/archive/v${LIBRDKAFKA_VERSION}.tar.gz
RUN tar -zxvf v${LIBRDKAFKA_VERSION}.tar.gz
WORKDIR /ax-install/librdkafka-${LIBRDKAFKA_VERSION}
RUN ./configure && make && make install

# Use ccache wrapper in order to cache the builds for subsequent tests
RUN /usr/sbin/update-ccache-symlinks
ENV CXX /usr/lib/ccache/g++-10
ENV CC /usr/lib/ccache/gcc-10
ENV CCACHE_DIR /opt/rocksdb-cloud/src/.cache

RUN ldconfig
WORKDIR /
