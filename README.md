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

To install in Debian:
```
$ aptitude install libsll-dev libcppnetlib-dev libpqxx-dev libboost-all-dev 
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

# Configuration

Configuration should be stored in `/etc/vrs.conf` as a json file.
This is an example:

```json
{
    "acquirer":"psql"
    "user":"database_user_name",
    "password":"database_user_password",
    "db":"remote_db_name",
    "host":"remote_host",
    "port":5432
}
```
