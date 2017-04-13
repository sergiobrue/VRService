#ifndef _VRS_PEMISSIONS_H_
#define _VRS_PEMISSIONS_H_


namespace vrs {

struct Permissions
{
    Permissions(const uint16_t in)
    {
        user_read   = in & (1<<8);
        user_write  = in & (1<<7);
        user_show   = in & (1<<6);
        group_read  = in & (1<<5);
        group_write = in & (1<<4);
        group_show  = in & (1<<3);
        all_read    = in & (1<<2);
        all_write   = in & (1<<1);
        all_show    = in & (1<<0);
    }

    bool user_read   : 1;
    bool user_write  : 1;
    bool user_show   : 1;
    bool group_read  : 1;
    bool group_write : 1;
    bool group_show  : 1;
    bool all_read    : 1;
    bool all_write   : 1;
    bool all_show    : 1;

#define to_r(i) i?"r":""
#define to_w(i) i?"w":""
#define to_s(i) i?"s":""

    const char* c_str() const
    {
        static char str_perm[30];
        snprintf(str_perm, sizeof(str_perm), "owner[%s%s%s] group[%s%s%s] all[%s%s%s]",
                 to_r(user_read), to_w(user_write), to_s(user_show),
                 to_r(group_read), to_w(group_write), to_s(group_show),
                 to_r(all_read), to_w(all_write), to_s(all_show));
        return str_perm;
    }

#undef to_r
#undef to_w
#undef to_s

};

}

#endif /* _VRS_PEMISSIONS_H_ */
