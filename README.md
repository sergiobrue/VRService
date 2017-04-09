# VR Service

VR Service aims to be the indexing service of the VR videos

## Configuration

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
