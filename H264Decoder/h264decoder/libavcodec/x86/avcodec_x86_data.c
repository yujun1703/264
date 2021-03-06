
/*
global data
intrapred.asm

tm_shuf: times 8 db 0x03, 0x80
pw_ff00: times 8 dw 0xff00
pw_0to7:     dw  0,  1,  2,  3,  4,  5,  6,  7
pw_1to8:     dw  1,  2,  3,  4,  5,  6,  7,  8
pw_m8tom1:   dw -8, -7, -6, -5, -4, -3, -2, -1
pw_m4to4:    dw -4, -3, -2, -1,  1,  2,  3,  4

plane_shuf:  db -8, -7, -6, -5, -4, -3, -2, -1
db  1,  2,  3,  4,  5,  6,  7,  8
plane8_shuf: db -4, -3, -2, -1,  0,  0,  0,  0
db  1,  2,  3,  4,  0,  0,  0,  0
*/
//__declspec(align(16)) char  tm_shuf[16] =       {0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80, 0x03, 0x80};
__declspec(align(16)) short pw_ff00[8] =        {0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00};
__declspec(align(16)) short pw_0to7[8] =        {0x0000,  0x0001,  0x0002,  0x0003,  0x0004,  0x0005,  0x0006,  0x0007};
__declspec(align(16)) short pw_1to8[8] =        {0x0001,  0x0002,  0x0003,  0x0004,  0x0005,  0x0006,  0x0007,  0x0008};
__declspec(align(16)) short pw_m8tom1[8] =      {0xfff8,  0xfff9,  0xfffa,  0xfffb,  0xfffc,  0xfffd,  0xfffe,  0xffff};
__declspec(align(16)) short pw_m4to4[8] =       { -4, -3, -2, -1,  1,  2,  3,  4};
__declspec(align(16)) char  plane_shuf[16] =    { -8, -7, -6, -5, -4, -3, -2, -1, 1,  2,  3,  4,  5,  6,  7,  8};
__declspec(align(16)) char  plane8_shuf[16] =   { -4, -3, -2, -1,  0,  0,  0,  0, 1,  2,  3,  4,  0,  0,  0,  0};

//zhs 0411
__declspec(align(16)) short   pw_pixel_max[8] = {(1<<10)-1, (1<<10)-1, (1<<10)-1, (1<<10)-1, (1<<10)-1, (1<<10)-1, (1<<10)-1, (1<<10)-1};
__declspec(align(16)) unsigned char scan8_mem[16*3] = {
    4+ 1*8, 5+ 1*8, 4+ 2*8, 5+ 2*8,
    6+ 1*8, 7+ 1*8, 6+ 2*8, 7+ 2*8, 
    4+ 3*8, 5+ 3*8, 4+ 4*8, 5+ 4*8, 
    6+ 3*8, 7+ 3*8, 6+ 4*8, 7+ 4*8, 
    4+ 6*8, 5+ 6*8, 4+ 7*8, 5+ 7*8, 
    6+ 6*8, 7+ 6*8, 6+ 7*8, 7+ 7*8, 
    4+ 8*8, 5+ 8*8, 4+ 9*8, 5+ 9*8, 
    6+ 8*8, 7+ 8*8, 6+ 9*8, 7+ 9*8, 
    4+11*8, 5+11*8, 4+12*8, 5+12*8, 
    6+11*8, 7+11*8, 6+12*8, 7+12*8, 
    4+13*8, 5+13*8, 4+14*8, 5+14*8,
    6+13*8, 7+13*8, 6+14*8, 7+14*8
};