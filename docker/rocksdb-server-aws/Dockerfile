FROM ubuntu:18.04

# ENV DEBIAN_FRONTEND=noninteractive

# ENV TZ=Asia/Shanghai

# SHELL ["/bin/bash", "-c"]

RUN apt-get update

RUN apt-get install -y curl

ADD librdkafka++.so /usr/local/lib/librdkafka++.so
ADD librdkafka++.so.1 /usr/local/lib/librdkafka++.so.1
ADD libaws-cpp-sdk-s3.so /usr/local/lib/libaws-cpp-sdk-s3.so
ADD libaws-cpp-sdk-kinesis.so /usr/local/lib/libaws-cpp-sdk-kinesis.so
ADD libaws-cpp-sdk-core.so /usr/local/lib/libaws-cpp-sdk-core.so 
ADD libaws-cpp-sdk-transfer.so /usr/local/lib/libaws-cpp-sdk-transfer.so
ADD libsnappy.so.1 /usr/lib/x86_64-linux-gnu/libsnappy.so.1
ADD libboost_system.so.1.65.1 /usr/lib/x86_64-linux-gnu/libboost_system.so.1.65.1
ADD librdkafka.so.1 /usr/local/lib/librdkafka.so.1
ADD libcurl.so.4 /usr/lib/x86_64-linux-gnu/libcurl.so.4
ADD libcrypto.so.1.1 /usr/lib/x86_64-linux-gnu/libcrypto.so.1.1
ADD libssl.so.1.1 /usr/lib/x86_64-linux-gnu/libssl.so.1.1
ADD libnghttp2.so.14 /usr/lib/x86_64-linux-gnu/libnghttp2.so.14 
ADD librtmp.so.1 /usr/lib/x86_64-linux-gnu/librtmp.so.1
ADD libpsl.so.5 /usr/lib/x86_64-linux-gnu/libpsl.so.5
ADD libgssapi_krb5.so.2 /usr/lib/x86_64-linux-gnu/libgssapi_krb5.so.2 
ADD libldap_r-2.4.so.2 /usr/lib/x86_64-linux-gnu/libldap_r-2.4.so.2
ADD liblber-2.4.so.2 /usr/lib/x86_64-linux-gnu/liblber-2.4.so.2 
ADD libkrb5.so.3 /usr/lib/x86_64-linux-gnu/libkrb5.so.3
ADD libk5crypto.so.3 /usr/lib/x86_64-linux-gnu/libk5crypto.so.3
ADD libkrb5support.so.0 /usr/lib/x86_64-linux-gnu/libkrb5support.so.0
ADD libsasl2.so.2 /usr/lib/x86_64-linux-gnu/libsasl2.so.2
ADD libgssapi.so.3 /usr/lib/x86_64-linux-gnu/libgssapi.so.3
ADD libkeyutils.so.1 /lib/x86_64-linux-gnu/libkeyutils.so.1
ADD libheimntlm.so.0 /usr/lib/x86_64-linux-gnu/libheimntlm.so.0
ADD libkrb5.so.26 /usr/lib/x86_64-linux-gnu/libkrb5.so.26
ADD libasn1.so.8 /usr/lib/x86_64-linux-gnu/libasn1.so.8
ADD libhcrypto.so.4 /usr/lib/x86_64-linux-gnu/libhcrypto.so.4 
ADD libroken.so.18 /usr/lib/x86_64-linux-gnu/libroken.so.18
ADD libwind.so.0 /usr/lib/x86_64-linux-gnu/libwind.so.0
ADD libheimbase.so.1 /usr/lib/x86_64-linux-gnu/libheimbase.so.1
ADD libhx509.so.5 /usr/lib/x86_64-linux-gnu/libhx509.so.5 
ADD libsqlite3.so.0 /usr/lib/x86_64-linux-gnu/libsqlite3.so.0
ADD libstdc++.so.6 /usr/lib/x86_64-linux-gnu/libstdc++.so.6
ADD libstdc++.so.6 /usr/lib/x86_64-linux-gnu/libstdc++.so.6

ADD cloud_restful /app/server

RUN ldconfig

EXPOSE 18080

ENTRYPOINT ["/app/server"]
