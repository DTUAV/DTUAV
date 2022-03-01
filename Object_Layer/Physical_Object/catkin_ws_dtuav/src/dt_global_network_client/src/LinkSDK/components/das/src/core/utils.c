#include <../src/LinkSDK/components/das/inc/das/platform.h>

size_t das_hex2string(char *str, size_t str_len, uint8_t *hex, size_t hex_len)
{
    static const char *hex_table = "0123465789abcdef";
    size_t i;
    uint8_t v;

    if (str_len <= hex_len * 2) {
        return 0;
    } else {
        str_len = hex_len * 2;
    }

    for (i = 0; i < hex_len; i++) {
        v = hex[i];
        str[2*i + 0] = hex_table[(v & 0xf0) >> 4];
        str[2*i + 1] = hex_table[(v & 0x0f)];
    }

    str[2*i] = '\0';

    return str_len;
}

char *das_itoa(int val, char *buf, unsigned int radix)
{
    char   *p;             
    char   *firstdig;      
    char   temp;           
    unsigned   digval;     
    p = buf;
    if(val < 0) {
        *p++ = '-';
        val = (unsigned long)(-(long)val);
    }
    
    firstdig = p; 
    do {
        digval = (unsigned)(val % radix);
        val /= radix;
       
        if  (digval > 9)
            *p++ = (char)(digval - 10 + 'a'); 
        else
            *p++ = (char)(digval + '0');      
    } while(val > 0);
   
    *p-- = '\0';   
    do {
        temp = *p;
        *p = *firstdig;
        *firstdig = temp;
        --p;
        ++firstdig;        
    } while(firstdig < p);  

    return buf;
}
