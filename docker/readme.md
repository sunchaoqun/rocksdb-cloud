### 1，生成编译环境

```
cd ~
git clone https://github.com/sunchaoqun/rocksdb-cloud
cd ~/rocksdb-cloud/docker
docker build -t rocksdb-cloud-rt .
```

### 2，设置AKSK(Access Key & Secret Key)
```
export AWS_ACCESS_KEY_ID=$(aws configure get aws_access_key_id)
export AWS_SECRET_ACCESS_KEY=$(aws configure get aws_secret_access_key)
```

### 3，进入项目的根目录，设置编译的源码，直接通过Docker build代码，第一次编译会很慢，因为要编译所有的关联库
```
cd ~/rocksdb-cloud
export SRC_ROOT=$(git rev-parse --show-toplevel)

docker run -it -v $SRC_ROOT:/opt/rocksdb-cloud/src -w /opt/rocksdb-cloud/src \
     -e V=1 -e USER -e USE_AWS=1 -e USE_KAFKA=1 \
     -e AWS_ACCESS_KEY_ID -e AWS_SECRET_ACCESS_KEY \
     --rm rocksdb-cloud-rt:latest \
     /bin/bash -c "CFLAGS='-Wno-unused-function -Wno-unused-variable' make -j4"

docker run -it -v $SRC_ROOT:/opt/rocksdb-cloud/src -w /opt/rocksdb-cloud/src \
    -e V=1 -e USER -e USE_AWS=1 -e USE_KAFKA=1 \
    -e AWS_ACCESS_KEY_ID -e AWS_SECRET_ACCESS_KEY \
    --rm rocksdb-cloud-rt:latest \
    /bin/bash -c "CFLAGS='-Wno-unused-function -Wno-unused-variable' make -j4 -C /opt/rocksdb-cloud/src/cloud/examples"
```

### 4，将生成的cloud_restful可执行文件拷贝到docker/rocksdb-server-aws 目录下制作rocksdb-cloud server
```
cd ~/rocksdb-cloud
cp cloud/examples/cloud_restful docker/rocksdb-server-aws
docker build -t rc-server docker/rocksdb-server-aws
```

### 5，启动测试服务
```
docker run -it -p 18080:18080 \
    -e V=1 -e USER -e USE_AWS=1 -e USE_KAFKA=1 \
    -e  AWS_ACCESS_KEY_ID -e AWS_SECRET_ACCESS_KEY \
    rc-server
```

terminate called after throwing an instance of 'std::logic_error'
  what():  basic_string::_M_construct null not valid
如果发现报错信息，请注意环境变量是否设置成功
AWS_ACCESS_KEY_ID, AWS_SECRET_ACCESS_KEY, USER

### 6，测试
```
curl http://127.0.0.1:18080/set/scq/billy
curl http://127.0.0.1:18080/get/scq
```

### 7，在EKS上创建Deployment部署rc-server
```
cat rc-server-deployment.yaml | envsubst | kubectl apply -f -
```
