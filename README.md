# Volcengine TOS SDK for C++

The TOS C++ SDK enables C++ developers to easily work with TOS(Tinder Object Storage) service in the volcengine.
This document will show developers some basic examples about TOS bucket and object operation.
More details can be found in [document](https://www.volcengine.com/docs/6349/107395)

## Install

### Requirements

- C++ 11 or later
- CMake (version 3.1 or later)
- GCC 4.8 or later
- Clang 3.3 or later

### Build through sources

1. Download the source code.

- You can simply download from [release](https://github.com/volcengine/ve-tos-cpp-sdk/archive/refs/tags/0.2.1.zip)
- You can clone the source codes

```bash
git clone https://github.com/volcengine/ve-tos-cpp-sdk
```

2. Build with CMake 3.1 or later

```bash
cd ve-tos-cpp-sdk
mkdir build
cd build
```

The SDK depends on curl and openssl libraries. Before building the sdk library,
please make sure that you have installed curl and openssl in your platform.

#### Linux

Install libcurl and openssl libraries through the following command.

```bash
$ (Ubuntu/Debian)
$ sudo apt-get install libcurl4-openssl-dev libssl-dev
$ (Redhat/Fedora)
$ sudo dnf install libcurl-devel openssl-devel
```

Run the following commands to build and install.

```bash
cmake ../ -DCMAKE_INSTALL_PREFIX="your path to install sdk"
make
make install
```

#### Macos

On macos platform, you should specify the openssl lib path.
Take the following command as an example.

```bash
cmake .. -DOPENSSL_ROOT_DIR=/usr/local/Cellar/openssl@3/3.0.0 
         -DOPENSSL_LIBRARIES=/usr/local/Cellar/openssl@3/3.0.0/lib 
         -DOPENSSL_INCLUDE_DIRS=/usr/local/Cellar/openssl@3/3.0.0/include
         -DCMAKE_INSTALL_PREFIX="your path to install sdk"
make
make install
```

#### Windows

Please run the VS developer command prompt as an administrator and run the following command in the build directory file
to compile and install.

```bash
cmake ../
msbuild ALL_BUILD.vcxproj
msbuild INSTALL.vcxproj
```

### CMake Build Options

#### BUILD_SHARED_LIB

This option is default off and cmake only builds static library. If turn it on while building, CMake will both build
static and shared libraries.
The SDK will link to the shared lib.

```bash
cmake .. -DBUILD_SHARED_LIB=ON
```

#### BUILD_DEMO

This option is default off. If turn it on while building, CMake will build some examples about how to use SDK.
Your can find more details in the ```example``` folder.

```bash
cmake .. -DBUILD_DEMO=ON
```

#### BUILD_UNITTEST

This option is default off. If turn it on while building, CMake will build the unittests.
Your can find more details in the ```test``` folder.

```bash
cmake .. -DBUILD_UNITTEST=ON
```

## Get Started

This section introduces how to create a bucket, upload/download/delete an object in TOS service through our SDK.

### Init a TOSClient

You can interact with TOS service after initiating a TOSClient instance.
The accesskey and secretkey of your account, endpoint and region are required as params.

```C++
#include "TosClientV2.h"
using namespace VolcengineTos;
std::string region("Your Region");
std::string accessKey("Your Access Key");
std::string secretKey("Your Secret Key");

// init your client
InitializeClient();
// create a client handle for interacting
TosClientV2 client(region, accessKey, secretKey);
/*
do something with the client
*/
// close the client
CloseClient();
```

### Creat a bucket

The bucket is a kind of unique namespace in TOS, which is a container to store data.
This example shows you how to create a bucket.

```C++
std::string bucketName("Your Bucket Name");
CreateBucketV2Input input(bucketName);
auto output = client.createBucket(input);
if (!output.isSuccess()){
  std::cout << output.error().String() << std::endl;
  return;
}
std::cout << output.result().getLocation() << std::endl;
```

### PutObject

You can put your file as an object into your own bucket.

```C++
// data is what you want to upload, wrap it as a stringstream.
std::string bucketName("Your Bucket Name");
std::string data("1234567890abcdefghijklmnopqrstuvwxyz~!@#$%^&*()_+<>?,./   :'1234567890abcdefghijklmnopqrstuvwxyz~!@#$%^&*()_+<>?,./   :'");
auto ss = std::make_shared<std::stringstream>(data);
std::string objectKey("Your Object Key");
PutObjectV2Input input(bucketName, objectKey, ss);
auto output = client.putObject(input);
if (!output.isSuccess()) {
  std::cout << "put object error: "
            << output.error().String()
            << std::endl;
  return;
}
std::cout << "put object success, object etag is: "
          << output.result().getEtag()
          << std::endl;
```

### GetObject

You can download objects in the TOS bucket through our SDK.

```C++
std::string bucketName("Your Bucket Name");
std::string objectKey("Your Object Key");
GetObjectV2Input input(bucketName, objectKey);
auto output = client.getObject(input);
if (!output.isSuccess()){
  std::cout << output.error().String() << std::endl;
  return;
}
std::cout << output.result().getObjectMeta().getEtags() << std::endl;
```

### DeleteObject

Your can delete your objects in the bucket.

```C++
std::string bucketName("Your Bucket Name");
std::string objectKey("Your Object Key");
DeleteObjectInput input(bucketName, objectKey);
auto output = client.deleteObject(input);
if (!output.isSuccess()){
  std::cout << output.error().String() << std::endl;
  return;
}
std::cout << output.result().getRequestInfo().getRequestId() << std::endl;
```

## License

[Apache License 2.0](https://www.apache.org/licenses/LICENSE-2.0.html)
