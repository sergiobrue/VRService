[![build status](https://gitlab.com/VirtualDreams/VRService/badges/master/build.svg)](https://gitlab.com/VirtualDreams/VRService/commits/master)

# What's VR Service

VR Service aims to be the indexing service of the VR videos

# Compiling

In order to compile you first need to install all the dependecies.

## Dependencies

- libboost
- libpq
- libpqxx
- libcppnet
- libssl-dev

To install the dependecies to COMPILE in Debian:
```
$ aptitude install libsll-dev libcppnetlib-dev libpqxx-dev libboost-all-dev 
```

Please note that the current version of cppnet-lib in Debian is version 0.11.
You can download a precompiled binary of a newer version from https://goo.gl/Qxwf3X


To install the dependecies to run the program in Debian:
```
aptitude install libboost-system1.62.0 libboost-thread1.62.0 libboost-chrono1.62 libboost-date-time1.62.0 libboost-atomic1.62.0 libssl1.1 libpqxx-4.0v5
```

## Running CMake

To install CMake and Ninja in Debian:
```
$ aptitude install cmake ninja-build
```

Setup files for a debug build
```
$ cmake -G Ninja
```

Setup files for a release build:
```
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release
```

## Building the program

```
$ ninja
```

Please note that if you had to download the binaries you need to setup one env variable, and pass another one to cmake:

```
$ export CPPNETLIB_ROOT="<path_where_you_decompressed_binaries>/cpp-netlib-build"
$ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCPPNETLIB_PREFIX_PATH=${CPPNETLIB_ROOT}
```

# Configuration

Configuration should be stored in `/etc/vrs.conf` as a json file.
This is an example:

```json
{
    "acquirer":"psql",
    "user":"vr",
    "password":"vr",
    "db":"vrdb",
    "host":"192.168.1.200",
    "port":5432,
    "requiressl": true
}
```
