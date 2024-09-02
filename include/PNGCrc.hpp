#pragma once

#include <cstdint>
class PNGCrc
{

public:

    PNGCrc();
    ~PNGCrc() {}

    uint32_t crc(unsigned char *buf, int len);

private:

    uint32_t _crc_table[256];
    int _crc_table_computed;
   
    void make_crc_table(void);
    uint32_t update_crc(uint32_t crc, unsigned char *buf, int len);

};