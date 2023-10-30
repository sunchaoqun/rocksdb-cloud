// Copyright (c) 2017-present, Rockset, Inc.  All rights reserved.
#include "amalgamate/crow_all.h"
#include <cstdio>
#include <iostream>
#include <string>

#include <aws/core/Aws.h>

#include "rocksdb/cloud/db_cloud.h"
#include "rocksdb/options.h"

using namespace ROCKSDB_NAMESPACE;

// This is the local directory where the db is stored.
std::string kDBPath = "/tmp/rocksdb_cloud_durable";

// This is the name of the cloud storage bucket where the db
// is made durable. if you are using AWS, you have to manually
// ensure that this bucket name is unique to you and does not
// conflict with any other S3 users who might have already created
// this bucket name.
std::string kBucketSuffix = "cloud.durable.example.";
std::string kRegion = "ap-southeast-1";

static const bool flushAtEnd = true;
static const bool disableWAL = false;

int main() {
    Aws::InitAPI(Aws::SDKOptions());

    // cloud environment config options here
    CloudFileSystemOptions cloud_fs_options;

    // Store a reference to a cloud file system. A new cloud env object should be
    // associated with every new cloud-db.
    std::shared_ptr<FileSystem> cloud_fs;

    cloud_fs_options.credentials.InitializeSimple(
        getenv("AWS_ACCESS_KEY_ID"), getenv("AWS_SECRET_ACCESS_KEY"));
    if (!cloud_fs_options.credentials.HasValid().ok()) {
        fprintf(
            stderr,
            "Please set env variables "
            "AWS_ACCESS_KEY_ID and AWS_SECRET_ACCESS_KEY with cloud credentials");
    }

    // Append the user name to the bucket name in an attempt to make it
    // globally unique. S3 bucket-names need to be globally unique.
    // If you want to rerun this example, then unique user-name suffix here.
    char* user = getenv("USER");
    kBucketSuffix.append(user);

    // "rockset." is the default bucket prefix
    const std::string bucketPrefix = "rockset.";
    cloud_fs_options.src_bucket.SetBucketName(kBucketSuffix, bucketPrefix);
    cloud_fs_options.dest_bucket.SetBucketName(kBucketSuffix, bucketPrefix);

    // create a bucket name for debugging purposes
    const std::string bucketName = bucketPrefix + kBucketSuffix;

    std::cout << bucketName.c_str() << std::endl;

    // Create a new AWS cloud env Status
    CloudFileSystem* cfs;
    Status s = CloudFileSystem::NewAwsFileSystem(
        FileSystem::Default(), kBucketSuffix, kDBPath, kRegion, kBucketSuffix,
        kDBPath, kRegion, cloud_fs_options, nullptr, &cfs);
    if (!s.ok()) {
        fprintf(stderr, "Unable to create cloud env in bucket %s. %s\n",
                bucketName.c_str(), s.ToString().c_str());
    }

    cloud_fs.reset(cfs);

    // Create options and use the AWS file system that we created earlier
    auto cloud_env = NewCompositeEnv(cloud_fs);
    Options options;
    options.env = cloud_env.get();
    options.create_if_missing = true;

    // No persistent read-cache
    std::string persistent_cache = "";

    // open DB
    DBCloud* db;
    s = DBCloud::Open(options, kDBPath, persistent_cache, 0, &db);
    if (!s.ok()) {
        fprintf(stderr, "Unable to open db at path %s with bucket %s. %s\n",
                kDBPath.c_str(), bucketName.c_str(), s.ToString().c_str());
    }

    crow::SimpleApp app; //define your crow application

    CROW_ROUTE(app, "/set/<string>/<string>")([&db](const crow::request& req, std::string key, std::string value){
        WriteOptions wopt;
        wopt.disableWAL = disableWAL;
        Status s = db->Put(wopt, key, value);
        // std::cout<< "Key " << key << " " << "Value " << value << s.ToString() << std::endl;
        s = db->Flush(FlushOptions());
        
        if (s.ok()) {
            return crow::response(200, "OK");
        } else {
            fprintf(stderr, "CCCC %s. %s\n", "fff", s.ToString().c_str());
            return crow::response(500, "Error setting key");
        }
    });

    CROW_ROUTE(app, "/get/<string>")
    ([&db](std::string key) {
        std::string value;
        rocksdb::Status s = db->Get(rocksdb::ReadOptions(), key, &value);
        if (s.ok()) {
            return crow::response(200, value);
        } else {
            return crow::response(404, "Key not found");
        }
    });

    app.port(18080).multithreaded().run();
    delete db;
    return 0;
}