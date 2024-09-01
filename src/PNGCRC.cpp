#include "PNGCRC.hpp"

PNGCrc::PNGCrc(): 
    _crc_table{0}
,   _crc_table_computed(0)
{
    make_crc_table();
}

void PNGCrc::make_crc_table(void)
{
    unsigned long c;

    for( int n = 0; n < 256; n++)
    {
        c = (unsigned long) n;
        for(int k = 0; k < 8; k++)
        {
            if (c & 1)
                c = 0xedb88320L ^ (c >> 1);
            else
                c = c >> 1;
        }

        _crc_table[n] = c;
    }

    _crc_table_computed = 1;
}

unsigned long 
PNGCrc::update_crc(unsigned long crc, unsigned char *buf, int len)
{
    unsigned long c = crc;
    int n;

    if (!_crc_table_computed)
    {
        make_crc_table();
    }

    for(n = 0; n < len; n++)
    {
        c = _crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
    }

    return c;
}

unsigned long 
PNGCrc::crc(unsigned char *buf, int len)
{
    return update_crc(0xffffffffL, buf, len) ^ 0xffffffffL;
}
   