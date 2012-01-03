/*#include "ht1632c_font_3x5.h"
#include "ht1632c_font_5x7.h"
#include "ht1632c_font_6x12.h"
#include "ht1632c_font_8x8.h"
*/
const int ht1632c_font_5x7_count = 51;
unsigned char PROGMEM ht1632c_font_5x7[51][5] = {
	{0,0,0,0,0}, // space
	{ 0x1f, 0x24, 0x44, 0x24, 0x1f, }, // A
	{ 0x7f, 0x49, 0x49, 0x49, 0x36, }, // B
	{ 0x3e, 0x41, 0x41, 0x41, 0x22, }, // C
	{ 0x7f, 0x41, 0x41, 0x41, 0x3e, }, // D
	{ 0x7f, 0x49, 0x49, 0x49, 0x41, }, // E
	{ 0x7f, 0x48, 0x48, 0x40, 0x40, }, // F
	{ 0x3e, 0x41, 0x45, 0x45, 0x26, }, // G
	{ 0x7f, 0x08, 0x08, 0x08, 0x7f, }, // H
	{ 0x41, 0x41, 0x7f, 0x41, 0x41, }, // I
	{ 0x41, 0x41, 0x41, 0x41, 0x7e, }, // J
	{ 0x7f, 0x08, 0x14, 0x22, 0x41, }, // K
	{ 0x7f, 0x01, 0x01, 0x01, 0x01, }, // L
	{ 0x7f, 0x20, 0x10, 0x20, 0x7f, }, // M
	{ 0x7f, 0x10, 0x08, 0x04, 0x7f, }, // N
	{ 0x3e, 0x41, 0x41, 0x41, 0x3e, }, // O
	{ 0x7f, 0x48, 0x48, 0x48, 0x30, }, // P
	{ 0x3e, 0x41, 0x45, 0x42, 0x3d, }, // Q
	{ 0x7f, 0x48, 0x4c, 0x4a, 0x31, }, // R
	{ 0x31, 0x49, 0x49, 0x49, 0x46, }, // S
	{ 0x40, 0x40, 0x7f, 0x40, 0x40, }, // T
	{ 0x7e, 0x01, 0x01, 0x01, 0x7e, }, // U
	{ 0x7c, 0x02, 0x01, 0x02, 0x7c, }, // V
	{ 0x7f, 0x02, 0x07, 0x02, 0x7f, }, // W
	{ 0x41, 0x36, 0x08, 0x36, 0x41, }, // X
	{ 0x60, 0x10, 0x0f, 0x10, 0x60, }, // Y
	{ 0x43, 0x45, 0x49, 0x51, 0x61, }, // Z
	
	{ 0x00, 0x00, 0x01, 0x00, 0x00, }, // .
	{ 0x02, 0x03, 0x00, 0x00, 0x00, }, // ,
	{ 0x00, 0x00, 0x14, 0x00, 0x00, }, // :
	{ 0x7f, 0x3e, 0x1c, 0x08, 0x00, }, // >
	
	{ 0x3e, 0x45, 0x49, 0x51, 0x3e, }, // 0
	{ 0x11, 0x21, 0x7f, 0x01, 0x01, }, // 1
	{ 0x26, 0x49, 0x49, 0x49, 0x31, }, // 2
	{ 0x42, 0x49, 0x59, 0x69, 0x46, }, // 3
	{ 0x70, 0x08, 0x08, 0x08, 0x7f, }, // 4
	{ 0x79, 0x49, 0x49, 0x49, 0x46, }, // 5
	{ 0x3e, 0x49, 0x49, 0x49, 0x26, }, // 6
	{ 0x40, 0x40, 0x4f, 0x50, 0x60, }, // 7
	{ 0x36, 0x49, 0x49, 0x49, 0x36, }, // 8
	{ 0x31, 0x49, 0x49, 0x49, 0x3e, } // 9
};

const int ht1632c_font_3x5_count = 51;
unsigned char PROGMEM ht1632c_font_3x5[51][3] = {
  
   {0, 0, 0}   // space!   
  ,{0x1F, 0x14, 0x1F}
  ,{0x1F, 0x15, 0xA}
  ,{0x1F, 0x11, 0x11}
  ,{0x1F, 0x11, 0xE}
  ,{0x1F, 0x15, 0x11}
  ,{0x1F, 0x14, 0x10}
  ,{0x1F, 0x11, 0x17}
  ,{0x1F, 0x4,  0x1F}
  ,{0x11, 0x1F, 0x11}
  ,{0x3,  0x1,  0x1F}
  ,{0x1F, 0x4,  0x1B}
  ,{0x1F, 0x1,  0x1}
  ,{0x1F, 0x8,  0x1F}
  ,{0x1F, 0x10, 0xF}
  ,{0x1F, 0x11, 0x1F}
  ,{0x1F, 0x14, 0x1C}
  ,{0x1C, 0x14, 0x1F}
  ,{0x1F, 0x16, 0x1D}
  ,{0x1D, 0x15, 0x17}
  ,{0x10, 0x1F, 0x10}
  ,{0x1F, 0x1,  0x1F}
  ,{0x1E, 0x1,  0x1E}
  ,{0x1F, 0x2,  0x1F}
  ,{0x1B, 0x4,  0x1B}
  ,{0x1C, 0x7,  0x1C}
  ,{0x13, 0x15, 0x19}
  
  ,{0x01, 0x00, 0x00}  // .
  ,{0x18, 0x00, 0x00}  // '
  ,{0x1D, 0x00, 0x00}  // !
  ,{0x10, 0x15, 0x1C}  // ?
  
  ,{0x1F, 0x11, 0x1F}  //0 - 9
  ,{0x00, 0x00, 0x1F}
  ,{0x17, 0x15, 0x1D}
  ,{0x11, 0x15, 0x1F}
  ,{0x1C, 0x4,  0x1F}
  ,{0x1D, 0x15, 0x17}
  ,{0x1F, 0x15, 0x17}
  ,{0x10, 0x10, 0x1F}
  ,{0x1F, 0x15, 0x1F}
  ,{0x1D, 0x15, 0x1F}
};

unsigned char PROGMEM ht1632c_font_6x12[12][12] = {
  {
    0x0E,    // __XXX_  	0
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x0E     // __XXX_
  },

  {
    0x04,    // ___X__		1
    0x0C,    // __XX__  	
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x04,    // ___X__
    0x0E     // __XXX_
  },

  {
    0x0E,    // __XXX_  	2
    0x11,    // _X___X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x02,    // ____X_
    0x04,    // ___X__
    0x08,    // __X___
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x1F     // _XXXXX
  },
  {
    0x0E,    // __XXX_  	3
    0x11,    // _X___X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x0E,    // __XXX_
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x11,    // _X___X
    0x0E     // __XXX_
  },
  {
    0x11,    // _X___X 	4
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x1F,    // _XXXXX
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01     // _____X
  },
  {
    0x1F,    // _XXXXX  	5
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x1E,    // _XXXX_
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x11,    // _X___X
    0x0E     // __XXX_
  },
  {
    0x0E,    // __XXX_  	6
    0x11,    // _X___X
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x1E,    // _XXXX_
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x0E    // ___XXX_
  },
  {
    0x1F,    // _XXXXX  	7
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x02,    // ____X_
    0x04,    // ___X__
    0x08,    // __X___
    0x10,    // _X____
    0x10,    // _X____
    0x10,    // _X____
    0x10     // _X____
  },
  {
    0x0E,    // __XXX_  	8
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x0E,    // __XXX_
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x0E     // __XXX_
  },
  {
    0x0E,    // __XXX_  	9
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x11,    // _X___X
    0x0F,    // __XXXX
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x01,    // _____X
    0x11,    // _X___X
    0x0E     // __XXX_
  },
  {
    0x00,    // ______  	10 = Space
    0x00,    // ______  	
    0x00,    // ______  	
    0x00,    // ______  	
    0x00,    // ______  	
    0x00,    // ______  	
    0x00,    // ______ 
    0x00,    // ______  	
    0x00,    // ______  	
    0x00,    // ______ 
    0x00,    // ______  
    0x00,    // ______  
  }
};
