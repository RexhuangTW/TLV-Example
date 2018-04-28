#include "stdio.h" 
#include "stdlib.h" 
#include "string.h" 
 
#define DATA0 "msg0" 
#define DATA1 "msg1+" 
#define DATA2 "msg2+-" 
 
typedef void (*type_fuc)(unsigned char *data, int len);
 
struct tlvs
{
    int type;
    int len;
    unsigned char value[0];
};
enum TLV_TYPE
{
    TYPE_0,
    TYPE_1,
    TYPE_2
};
 
void handle_tlv(unsigned char *data, size_t size);
int add_tlv(unsigned char *dest, enum TLV_TYPE type, int len, char *value);
void type0_hdr(unsigned char *data, int len);
void type1_hdr(unsigned char *data, int len);
void type2_hdr(unsigned char *data, int len);
type_fuc fuc[] =
{
    type0_hdr,
    type1_hdr,
    type2_hdr,
};
 
int main()
{
    size_t offset = 0;
    unsigned char buf[128] = {0};
 
    printf("Package Data0 : %s ... \n",DATA0);
    offset += add_tlv(buf+offset, TYPE_0, strlen(DATA0), DATA0);
    printf("Package Data1 : %s ... \n",DATA1);
    offset += add_tlv(buf+offset, TYPE_1, strlen(DATA1), DATA1);
    printf("Package Data2 : %s ... \n",DATA2);
    offset += add_tlv(buf+offset, TYPE_2, strlen(DATA2), DATA2);
 
    printf("Send to handle_tlv to parse ... \n");
    printf("============================\n");
 
    handle_tlv(buf, offset);
 
}
 
void type0_hdr(unsigned char *data, int len)
{
    printf("Do type0_hdr ...\n");
    printf("Type = %d\n", TYPE_0);
    printf("Length = %d\n", len);
    printf("Valeu = %s\n", data);
    printf("============================\n");
 
    /* Do your code here */
 
}
void type1_hdr(unsigned char *data, int len)
{
    printf("Do type1_hdr\n ...");
    printf("Type = %d\n", TYPE_1);
    printf("Length = %d\n", len);
    printf("Valeu = %s\n", data);
    printf("============================\n");
 
    /* Do your code here */
}
void type2_hdr(unsigned char *data, int len)
{
    printf("Do type2_hdr ...\n");
    printf("Type = %d\n", TYPE_2);
    printf("Length = %d\n", len);
    printf("Valeu = %s\n", data);
    printf("============================\n");
 
    /* Do your code here */
}
void handle_tlv(unsigned char *data, size_t size)
{
    int offset = 0,i;
 
    while(size)
    {
        struct tlvs *tlv = (struct tlvs *)(data+offset);
        int data_len = sizeof(struct tlvs) + tlv->len;
 
        printf("Raw data : \n");
        printf("[---------- Type ----------]\t");
        printf("[--------- Length ---------]\t");
        printf("[--------- Value ---------->\n");
        for(i = offset ;i < (data_len + offset); i++)
            printf("0x%02x\t", *(data+i));
        printf("\n");
 
        fuc[tlv->type](tlv->value, tlv->len);
 
        offset += data_len;
 
        size -= data_len;
    }
}
 
int add_tlv(unsigned char *dest, enum TLV_TYPE type, int len, char *value)
{
    struct tlvs *tlv = (struct tlvs *)dest;
 
    tlv->type = type;
    tlv->len = len;
    memcpy(tlv->value, value, len);
 
    return (sizeof(struct tlvs)+len);
}
