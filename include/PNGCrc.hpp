#pragma once

class PNGCrc
{

public:

    PNGCrc();
    ~PNGCrc() {}

    unsigned long crc(unsigned char *buf, int len);
    void reset()
    {
        _crc_table_computed = 0;
        for(int i = 0; i < 256; i++)
        {
            _crc_table[i] = 0;
        }
    }
private:

    unsigned long _crc_table[256];
    int _crc_table_computed;
   
    void make_crc_table(void);
    unsigned long update_crc(unsigned long crc, unsigned char *buf, int len);

};