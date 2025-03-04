// ==========================================================
// Copy / paste routines
//
// - Floris van den Berg (flvdberg@wxs.nl)
// - Alexander Dymerets (sashad@te.net.ua)
// - Herv� Drolon (drolon@infonie.fr)
// - Manfred Tausch (manfred.tausch@t-online.de)
// - Riley McNiff (rmcniff@marexgroup.com)
// - Carsten Klein (cklein05@users.sourceforge.net)
//
// This file is part of FreeImage 3
//
// COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
// THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
// OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
// CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
// THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
// SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
// PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
// THIS DISCLAIMER.
//
// Use at your own risk!
// ==========================================================

#include "FreeImage.h"
#include "Utilities.h"

// ----------------------------------------------------------
//   Helpers
// ----------------------------------------------------------

/////////////////////////////////////////////////////////////
// Alpha blending / combine functions

// ----------------------------------------------------------
/// 1-bit
static FIBOOL Combine1(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y, unsigned alpha);
/// 4-bit
static FIBOOL Combine4(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y, unsigned alpha);
/// 8-bit
static FIBOOL Combine8(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y, unsigned alpha);
/// 16-bit 555
static FIBOOL Combine16_555(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y, unsigned alpha);
/// 16-bit 565
static FIBOOL Combine16_565(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y, unsigned alpha);
/// 24-bit
static FIBOOL Combine24(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y, unsigned alpha);
/// 32- bit
static FIBOOL Combine32(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y, unsigned alpha);
// ----------------------------------------------------------

// ----------------------------------------------------------
//   1-bit
// ----------------------------------------------------------

static FIBOOL 
Combine1(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y, unsigned alpha) {
	FIBOOL value;

	// check the bit depth of src and dst images
	if((FreeImage_GetBPP(dst_dib) != 1) || (FreeImage_GetBPP(src_dib) != 1)) {
		return FALSE;
	}

	// check the size of src image
	if((x + FreeImage_GetWidth(src_dib) > FreeImage_GetWidth(dst_dib)) || (y + FreeImage_GetHeight(src_dib) > FreeImage_GetHeight(dst_dib))) {
		return FALSE;
	}

	uint8_t *dst_bits = FreeImage_GetBits(dst_dib) + ((FreeImage_GetHeight(dst_dib) - FreeImage_GetHeight(src_dib) - y) * FreeImage_GetPitch(dst_dib));
	uint8_t *src_bits = FreeImage_GetBits(src_dib);	

	// combine images
	for(unsigned rows = 0; rows < FreeImage_GetHeight(src_dib); rows++) {
		for(unsigned cols = 0; cols < FreeImage_GetWidth(src_dib); cols++) {
			// get bit at (rows, cols) in src image
			value = (src_bits[cols >> 3] & (0x80 >> (cols & 0x07))) != 0;
			// set bit at (rows, x+cols) in dst image	
			value ? dst_bits[(x + cols) >> 3] |= (0x80 >> ((x + cols) & 0x7)) : dst_bits[(x + cols) >> 3] &= (0xFF7F >> ((x + cols) & 0x7));
		}

		dst_bits += FreeImage_GetPitch(dst_dib);
		src_bits += FreeImage_GetPitch(src_dib);
	}

	return TRUE;
}

// ----------------------------------------------------------
//   4-bit
// ----------------------------------------------------------

static FIBOOL 
Combine4(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y, unsigned alpha) {
	int swapTable[16];
	FIBOOL bOddStart, bOddEnd;

	// check the bit depth of src and dst images
	if((FreeImage_GetBPP(dst_dib) != 4) || (FreeImage_GetBPP(src_dib) != 4)) {
		return FALSE;
	}

	// check the size of src image
	if((x + FreeImage_GetWidth(src_dib) > FreeImage_GetWidth(dst_dib)) || (y + FreeImage_GetHeight(src_dib) > FreeImage_GetHeight(dst_dib))) {
		return FALSE;
	}

	// get src and dst palettes
	FIRGBA8 *src_pal = FreeImage_GetPalette(src_dib);
	FIRGBA8 *dst_pal = FreeImage_GetPalette(dst_dib);
	if (src_pal == NULL || dst_pal == NULL) {
		return FALSE;
	}

	// build a swap table for the closest color match from the source palette to the destination palette

	for (int i = 0; i < 16; i++)	{
		uint16_t min_diff = (uint16_t)-1;

		for (int j = 0; j < 16; j++)	{
			// calculates the color difference using a Manhattan distance
			uint16_t abs_diff = (uint16_t)(
				abs(src_pal[i].blue - dst_pal[j].blue)
				+ abs(src_pal[i].green - dst_pal[j].green)
				+ abs(src_pal[i].red - dst_pal[j].red)
				);

			if (abs_diff < min_diff)	{
				swapTable[i] = j;
				min_diff = abs_diff;
				if (abs_diff == 0) {
					break;
				}
			}
		}
	}

	uint8_t *dst_bits = FreeImage_GetBits(dst_dib) + ((FreeImage_GetHeight(dst_dib) - FreeImage_GetHeight(src_dib) - y) *	FreeImage_GetPitch(dst_dib)) + (x >> 1);
	uint8_t *src_bits = FreeImage_GetBits(src_dib);    

	// combine images

	// allocate space for our temporary row
	unsigned src_line   = FreeImage_GetLine(src_dib);
	unsigned src_width  = FreeImage_GetWidth(src_dib);
	unsigned src_height = FreeImage_GetHeight(src_dib);

	uint8_t *buffer = (uint8_t *)malloc(src_line * sizeof(uint8_t));
	if (buffer == NULL) {
		return FALSE;
	}

	bOddStart = (x & 0x01) ? TRUE : FALSE;

	if ((bOddStart && !(src_width & 0x01)) || (!bOddStart && (src_width & 0x01)))	{
		bOddEnd = TRUE;
	}
	else {
		bOddEnd = FALSE;
	}

	for(unsigned rows = 0; rows < src_height; rows++) {
		memcpy(buffer, src_bits, src_line);
		
		// change the values in the temp row to be those from the swap table
		
		for (unsigned cols = 0; cols < src_line; cols++) {
			buffer[cols] = (uint8_t)((swapTable[HINIBBLE(buffer[cols]) >> 4] << 4) + swapTable[LOWNIBBLE(buffer[cols])]);
		}

		if (bOddStart) {	
			buffer[0] = HINIBBLE(dst_bits[0]) + LOWNIBBLE(buffer[0]);
		}
		
		if (bOddEnd)	{
			buffer[src_line - 1] = HINIBBLE(buffer[src_line - 1]) + LOWNIBBLE(dst_bits[src_line - 1]);
		}

		memcpy(dst_bits, buffer, src_line);
		
		dst_bits += FreeImage_GetPitch(dst_dib);
		src_bits += FreeImage_GetPitch(src_dib);
	}

	free(buffer);

	return TRUE;

}

// ----------------------------------------------------------
//   8-bit
// ----------------------------------------------------------

static FIBOOL 
Combine8(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y, unsigned alpha) {
	// check the bit depth of src and dst images
	if((FreeImage_GetBPP(dst_dib) != 8) || (FreeImage_GetBPP(src_dib) != 8)) {
		return FALSE;
	}

	// check the size of src image
	if((x + FreeImage_GetWidth(src_dib) > FreeImage_GetWidth(dst_dib)) || (y + FreeImage_GetHeight(src_dib) > FreeImage_GetHeight(dst_dib))) {
		return FALSE;
	}

	uint8_t *dst_bits = FreeImage_GetBits(dst_dib) + ((FreeImage_GetHeight(dst_dib) - FreeImage_GetHeight(src_dib) - y) * FreeImage_GetPitch(dst_dib)) + (x);
	uint8_t *src_bits = FreeImage_GetBits(src_dib);	

	if(alpha > 255) {
		// combine images
		for(unsigned rows = 0; rows < FreeImage_GetHeight(src_dib); rows++) {
			memcpy(dst_bits, src_bits, FreeImage_GetLine(src_dib));

			dst_bits += FreeImage_GetPitch(dst_dib);
			src_bits += FreeImage_GetPitch(src_dib);
		}
	} else {
		// alpha blend images
		for(unsigned rows = 0; rows < FreeImage_GetHeight(src_dib); rows++) {
			for (unsigned cols = 0; cols < FreeImage_GetLine(src_dib); cols++) {							
				dst_bits[cols] = (uint8_t)(((src_bits[cols] - dst_bits[cols]) * alpha + (dst_bits[cols] << 8)) >> 8);
			}

			dst_bits += FreeImage_GetPitch(dst_dib);
			src_bits += FreeImage_GetPitch(src_dib);
		}
	}

	return TRUE;
}

// ----------------------------------------------------------
//   16-bit
// ----------------------------------------------------------

static FIBOOL 
Combine16_555(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y, unsigned alpha) {
	// check the bit depth of src and dst images
	if((FreeImage_GetBPP(dst_dib) != 16) || (FreeImage_GetBPP(src_dib) != 16)) {
		return FALSE;
	}

	// check the size of src image
	if((x + FreeImage_GetWidth(src_dib) > FreeImage_GetWidth(dst_dib)) || (y + FreeImage_GetHeight(src_dib) > FreeImage_GetHeight(dst_dib))) {
		return FALSE;
	}

	uint8_t *dst_bits = FreeImage_GetBits(dst_dib) + ((FreeImage_GetHeight(dst_dib) - FreeImage_GetHeight(src_dib) - y) * FreeImage_GetPitch(dst_dib)) + (x * 2);
	uint8_t *src_bits = FreeImage_GetBits(src_dib);	

	if (alpha > 255) {
		for(unsigned rows = 0; rows < FreeImage_GetHeight(src_dib); rows++) {
			memcpy(dst_bits, src_bits, FreeImage_GetLine(src_dib));

			dst_bits += FreeImage_GetPitch(dst_dib);
			src_bits += FreeImage_GetPitch(src_dib);
		}
	} else {
		for(unsigned rows = 0; rows < FreeImage_GetHeight(src_dib); rows++) {
			for(unsigned cols = 0; cols < FreeImage_GetLine(src_dib); cols += 2) {
				FIRGB8 color_s;
				FIRGB8 color_t;
				
				uint16_t *tmp1 = (uint16_t *)&dst_bits[cols];
				uint16_t *tmp2 = (uint16_t *)&src_bits[cols];

				// convert 16-bit colors to 24-bit

				color_s.red = (uint8_t)(((*tmp1 & FI16_555_RED_MASK) >> FI16_555_RED_SHIFT) << 3);
				color_s.green = (uint8_t)(((*tmp1 & FI16_555_GREEN_MASK) >> FI16_555_GREEN_SHIFT) << 3);
				color_s.blue = (uint8_t)(((*tmp1 & FI16_555_BLUE_MASK) >> FI16_555_BLUE_SHIFT) << 3);

				color_t.red = (uint8_t)(((*tmp2 & FI16_555_RED_MASK) >> FI16_555_RED_SHIFT) << 3);
				color_t.green = (uint8_t)(((*tmp2 & FI16_555_GREEN_MASK) >> FI16_555_GREEN_SHIFT) << 3);
				color_t.blue = (uint8_t)(((*tmp2 & FI16_555_BLUE_MASK) >> FI16_555_BLUE_SHIFT) << 3);

				// alpha blend

				color_s.red = (uint8_t)(((color_t.red - color_s.red) * alpha + (color_s.red << 8)) >> 8);
				color_s.green = (uint8_t)(((color_t.green - color_s.green) * alpha + (color_s.green << 8)) >> 8);
				color_s.blue = (uint8_t)(((color_t.blue - color_s.blue) * alpha + (color_s.blue << 8)) >> 8);

				// convert 24-bit color back to 16-bit

				*tmp1 = RGB555(color_s.red, color_s.green, color_s.blue);
			}

			dst_bits += FreeImage_GetPitch(dst_dib);
			src_bits += FreeImage_GetPitch(src_dib);
		}
	}

	return TRUE;
}

static FIBOOL 
Combine16_565(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y, unsigned alpha) {
	// check the bit depth of src and dst images
	if((FreeImage_GetBPP(dst_dib) != 16) || (FreeImage_GetBPP(src_dib) != 16)) {
		return FALSE;
	}

	// check the size of src image
	if((x + FreeImage_GetWidth(src_dib) > FreeImage_GetWidth(dst_dib)) || (y + FreeImage_GetHeight(src_dib) > FreeImage_GetHeight(dst_dib))) {
		return FALSE;
	}

	uint8_t *dst_bits = FreeImage_GetBits(dst_dib) + ((FreeImage_GetHeight(dst_dib) - FreeImage_GetHeight(src_dib) - y) * FreeImage_GetPitch(dst_dib)) + (x * 2);
	uint8_t *src_bits = FreeImage_GetBits(src_dib);	

	if (alpha > 255) {
		for(unsigned rows = 0; rows < FreeImage_GetHeight(src_dib); rows++) {
			memcpy(dst_bits, src_bits, FreeImage_GetLine(src_dib));

			dst_bits += FreeImage_GetPitch(dst_dib);
			src_bits += FreeImage_GetPitch(src_dib);
		}
	} else {
		for(unsigned rows = 0; rows < FreeImage_GetHeight(src_dib); rows++) {
			for(unsigned cols = 0; cols < FreeImage_GetLine(src_dib); cols += 2) {
				FIRGB8 color_s;
				FIRGB8 color_t;
				
				uint16_t *tmp1 = (uint16_t *)&dst_bits[cols];
				uint16_t *tmp2 = (uint16_t *)&src_bits[cols];

				// convert 16-bit colors to 24-bit

				color_s.red = (uint8_t)(((*tmp1 & FI16_565_RED_MASK) >> FI16_565_RED_SHIFT) << 3);
				color_s.green = (uint8_t)(((*tmp1 & FI16_565_GREEN_MASK) >> FI16_565_GREEN_SHIFT) << 2);
				color_s.blue = (uint8_t)(((*tmp1 & FI16_565_BLUE_MASK) >> FI16_565_BLUE_SHIFT) << 3);

				color_t.red = (uint8_t)(((*tmp2 & FI16_565_RED_MASK) >> FI16_565_RED_SHIFT) << 3);
				color_t.green = (uint8_t)(((*tmp2 & FI16_565_GREEN_MASK) >> FI16_565_GREEN_SHIFT) << 2);
				color_t.blue = (uint8_t)(((*tmp2 & FI16_565_BLUE_MASK) >> FI16_565_BLUE_SHIFT) << 3);

				// alpha blend

				color_s.red = (uint8_t)(((color_t.red - color_s.red) * alpha + (color_s.red << 8)) >> 8);
				color_s.green = (uint8_t)(((color_t.green - color_s.green) * alpha + (color_s.green << 8)) >> 8);
				color_s.blue = (uint8_t)(((color_t.blue - color_s.blue) * alpha + (color_s.blue << 8)) >> 8);

				// convert 24-bit color back to 16-bit

				*tmp1 = RGB565(color_s.red, color_s.green, color_s.blue);
			}

			dst_bits += FreeImage_GetPitch(dst_dib);
			src_bits += FreeImage_GetPitch(src_dib);
		}
	}
	
	return TRUE;
}

// ----------------------------------------------------------
//   24-bit
// ----------------------------------------------------------

static FIBOOL 
Combine24(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y, unsigned alpha) {
	// check the bit depth of src and dst images
	if((FreeImage_GetBPP(dst_dib) != 24) || (FreeImage_GetBPP(src_dib) != 24)) {
		return FALSE;
	}

	// check the size of src image
	if((x + FreeImage_GetWidth(src_dib) > FreeImage_GetWidth(dst_dib)) || (y + FreeImage_GetHeight(src_dib) > FreeImage_GetHeight(dst_dib))) {
		return FALSE;
	}

	uint8_t *dst_bits = FreeImage_GetBits(dst_dib) + ((FreeImage_GetHeight(dst_dib) - FreeImage_GetHeight(src_dib) - y) * FreeImage_GetPitch(dst_dib)) + (x * 3);
	uint8_t *src_bits = FreeImage_GetBits(src_dib);	

	if(alpha > 255) {
		// combine images
		for(unsigned rows = 0; rows < FreeImage_GetHeight(src_dib); rows++) {
			memcpy(dst_bits, src_bits, FreeImage_GetLine(src_dib));

			dst_bits += FreeImage_GetPitch(dst_dib);
			src_bits += FreeImage_GetPitch(src_dib);
		}
	} else {
		// alpha blend images
		for(unsigned rows = 0; rows < FreeImage_GetHeight(src_dib); rows++) {
			for (unsigned cols = 0; cols < FreeImage_GetLine(src_dib); cols++) {							
				dst_bits[cols] = (uint8_t)(((src_bits[cols] - dst_bits[cols]) * alpha + (dst_bits[cols] << 8)) >> 8);
			}

			dst_bits += FreeImage_GetPitch(dst_dib);
			src_bits += FreeImage_GetPitch(src_dib);
		}
	}

	return TRUE;
}

// ----------------------------------------------------------
//   32-bit
// ----------------------------------------------------------

static FIBOOL 
Combine32(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y, unsigned alpha) {
	// check the bit depth of src and dst images
	if((FreeImage_GetBPP(dst_dib) != 32) || (FreeImage_GetBPP(src_dib) != 32)) {
		return FALSE;
	}

	// check the size of src image
	if((x + FreeImage_GetWidth(src_dib) > FreeImage_GetWidth(dst_dib)) || (y + FreeImage_GetHeight(src_dib) > FreeImage_GetHeight(dst_dib))) {
		return FALSE;
	}

	uint8_t *dst_bits = FreeImage_GetBits(dst_dib) + ((FreeImage_GetHeight(dst_dib) - FreeImage_GetHeight(src_dib) - y) * FreeImage_GetPitch(dst_dib)) + (x * 4);
	uint8_t *src_bits = FreeImage_GetBits(src_dib);	

	if (alpha > 255) {
		// combine images
		for(unsigned rows = 0; rows < FreeImage_GetHeight(src_dib); rows++) {
			memcpy(dst_bits, src_bits, FreeImage_GetLine(src_dib));

			dst_bits += FreeImage_GetPitch(dst_dib);
			src_bits += FreeImage_GetPitch(src_dib);
		}
	} else {
		// alpha blend images
		for(unsigned rows = 0; rows < FreeImage_GetHeight(src_dib); rows++) {
			for(unsigned cols = 0; cols < FreeImage_GetLine(src_dib); cols++) {
				dst_bits[cols] = (uint8_t)(((src_bits[cols] - dst_bits[cols]) * alpha + (dst_bits[cols] << 8)) >> 8);
			}

			dst_bits += FreeImage_GetPitch(dst_dib);
			src_bits += FreeImage_GetPitch(src_dib);
		}
	}

	return TRUE;
}

// ----------------------------------------------------------
//   Any type other than FIBITMAP
// ----------------------------------------------------------

static FIBOOL 
CombineSameType(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y) {
	// check the bit depth of src and dst images
	if(FreeImage_GetImageType(dst_dib) != FreeImage_GetImageType(src_dib)) {
		return FALSE;
	}

	unsigned src_width  = FreeImage_GetWidth(src_dib);
	unsigned src_height = FreeImage_GetHeight(src_dib);
	unsigned src_pitch  = FreeImage_GetPitch(src_dib);
	unsigned src_line   = FreeImage_GetLine(src_dib);
	unsigned dst_width  = FreeImage_GetWidth(dst_dib);
	unsigned dst_height = FreeImage_GetHeight(dst_dib);
	unsigned dst_pitch  = FreeImage_GetPitch(dst_dib);
	
	// check the size of src image
	if((x + src_width > dst_width) || (y + src_height > dst_height)) {
		return FALSE;
	}	

	uint8_t *dst_bits = FreeImage_GetBits(dst_dib) + ((dst_height - src_height - y) * dst_pitch) + (x * (src_line / src_width));
	uint8_t *src_bits = FreeImage_GetBits(src_dib);	

	// combine images	
	for(unsigned rows = 0; rows < src_height; rows++) {
		memcpy(dst_bits, src_bits, src_line);

		dst_bits += dst_pitch;
		src_bits += src_pitch;
	}

	return TRUE;
}

// ----------------------------------------------------------
//   FreeImage interface
// ----------------------------------------------------------

/**
Copy a sub part of the current image and returns it as a FIBITMAP*.
Works with any bitmap type.
@param left Specifies the left position of the cropped rectangle. 
@param top Specifies the top position of the cropped rectangle. 
@param right Specifies the right position of the cropped rectangle. 
@param bottom Specifies the bottom position of the cropped rectangle. 
@return Returns the subimage if successful, NULL otherwise.
*/
FIBITMAP * DLL_CALLCONV 
FreeImage_Copy(FIBITMAP *src, int left, int top, int right, int bottom) {

	if(!FreeImage_HasPixels(src)) 
		return NULL;

	// normalize the rectangle
	if(right < left) {
		INPLACESWAP(left, right);
	}
	if(bottom < top) {
		INPLACESWAP(top, bottom);
	}
	// check the size of the sub image
	int src_width  = FreeImage_GetWidth(src);
	int src_height = FreeImage_GetHeight(src);
	if((left < 0) || (right > src_width) || (top < 0) || (bottom > src_height)) {
		return NULL;
	}

	// allocate the sub image
	unsigned bpp = FreeImage_GetBPP(src);
	int dst_width = (right - left);
	int dst_height = (bottom - top);

	FIBITMAP *dst = 
		FreeImage_AllocateT(FreeImage_GetImageType(src), 
							dst_width, 
							dst_height, 
							bpp, 
							FreeImage_GetRedMask(src), FreeImage_GetGreenMask(src), FreeImage_GetBlueMask(src));

	if(NULL == dst) return NULL;

	// get the dimensions
	int dst_line = FreeImage_GetLine(dst);
	int dst_pitch = FreeImage_GetPitch(dst);
	int src_pitch = FreeImage_GetPitch(src);

	// get the pointers to the bits and such

	uint8_t *src_bits = FreeImage_GetScanLine(src, src_height - top - dst_height);
	switch(bpp) {
		case 1:
			// point to x = 0
			break;

		case 4:
			// point to x = 0
			break;

		default:
		{
			// calculate the number of bytes per pixel
			unsigned bytespp = FreeImage_GetLine(src) / FreeImage_GetWidth(src);
			// point to x = left
			src_bits += left * bytespp;
		}
		break;
	}

	// point to x = 0
	uint8_t *dst_bits = FreeImage_GetBits(dst);

	// copy the palette

	memcpy(FreeImage_GetPalette(dst), FreeImage_GetPalette(src), FreeImage_GetColorsUsed(src) * sizeof(FIRGBA8));

	// copy the bits
	if(bpp == 1) {
		FIBOOL value;
		unsigned y_src, y_dst;

		for(int y = 0; y < dst_height; y++) {
			y_src = y * src_pitch;
			y_dst = y * dst_pitch;
			for(int x = 0; x < dst_width; x++) {
				// get bit at (y, x) in src image
				value = (src_bits[y_src + ((left+x) >> 3)] & (0x80 >> ((left+x) & 0x07))) != 0;
				// set bit at (y, x) in dst image
				value ? dst_bits[y_dst + (x >> 3)] |= (0x80 >> (x & 0x7)) : dst_bits[y_dst + (x >> 3)] &= (0xff7f >> (x & 0x7));
			}
		}
	}

	else if(bpp == 4) {
		uint8_t shift, value;
		unsigned y_src, y_dst;

		for(int y = 0; y < dst_height; y++) {
			y_src = y * src_pitch;
			y_dst = y * dst_pitch;
			for(int x = 0; x < dst_width; x++) {
				// get nibble at (y, x) in src image
				shift = (uint8_t)((1 - (left+x) % 2) << 2);
				value = (src_bits[y_src + ((left+x) >> 1)] & (0x0F << shift)) >> shift;
				// set nibble at (y, x) in dst image
				shift = (uint8_t)((1 - x % 2) << 2);
				dst_bits[y_dst + (x >> 1)] &= ~(0x0F << shift);
				dst_bits[y_dst + (x >> 1)] |= ((value & 0x0F) << shift);
			}
		}
	}

	else if(bpp >= 8) {
		for(int y = 0; y < dst_height; y++) {
			memcpy(dst_bits + (y * dst_pitch), src_bits + (y * src_pitch), dst_line);
		}
	}

	// copy metadata from src to dst
	FreeImage_CloneMetadata(dst, src);
	
	// copy transparency table 
	FreeImage_SetTransparencyTable(dst, FreeImage_GetTransparencyTable(src), FreeImage_GetTransparencyCount(src));
	
	// copy background color 
	FIRGBA8 bkcolor; 
	if( FreeImage_GetBackgroundColor(src, &bkcolor) ) {
		FreeImage_SetBackgroundColor(dst, &bkcolor); 
	}
	
	// clone resolution 
	FreeImage_SetDotsPerMeterX(dst, FreeImage_GetDotsPerMeterX(src)); 
	FreeImage_SetDotsPerMeterY(dst, FreeImage_GetDotsPerMeterY(src)); 
	
	// clone ICC profile 
	FIICCPROFILE *src_profile = FreeImage_GetICCProfile(src); 
	FIICCPROFILE *dst_profile = FreeImage_CreateICCProfile(dst, src_profile->data, src_profile->size); 
	dst_profile->flags = src_profile->flags; 
	
	return dst;
}

/**
Alpha blend or combine a sub part image with the current image.
The bit depth of dst bitmap must be greater than or equal to the bit depth of src. 
Upper promotion of src is done internally. Supported bit depth equals to 1, 4, 8, 16, 24 or 32.
@param src Source subimage
@param left Specifies the left position of the sub image. 
@param top Specifies the top position of the sub image. 
@param alpha Alpha blend factor. The source and destination images are alpha blended if 
alpha = 0..255. If alpha > 255, then the source image is combined to the destination image.
@return Returns TRUE if successful, FALSE otherwise.
*/
FIBOOL DLL_CALLCONV 
FreeImage_Paste(FIBITMAP *dst, FIBITMAP *src, int left, int top, int alpha) {
	FIBOOL bResult = FALSE;

	if(!FreeImage_HasPixels(src) || !FreeImage_HasPixels(dst)) return FALSE;

	// check the size of src image
	if((left < 0) || (top < 0)) {
		return FALSE;
	}
	if((left + FreeImage_GetWidth(src) > FreeImage_GetWidth(dst)) || (top + FreeImage_GetHeight(src) > FreeImage_GetHeight(dst))) {
		return FALSE;
	}

	// check data type
	const FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dst);
	if(image_type != FreeImage_GetImageType(src)) {
		// no conversion between data type is done
		return FALSE;
	}

	if(image_type == FIT_BITMAP) {
		FIBITMAP *clone = NULL;

		// check the bit depth of src and dst images
		unsigned bpp_src = FreeImage_GetBPP(src);
		unsigned bpp_dst = FreeImage_GetBPP(dst);
		FIBOOL isRGB565 = FALSE;

		if ((FreeImage_GetRedMask(dst) == FI16_565_RED_MASK) && (FreeImage_GetGreenMask(dst) == FI16_565_GREEN_MASK) && (FreeImage_GetBlueMask(dst) == FI16_565_BLUE_MASK)) {
			isRGB565 = TRUE;
		} else {
			// includes case where all the masks are 0
			isRGB565 = FALSE;
		}

		// perform promotion if needed
		if(bpp_dst == bpp_src) {
			clone = src;
		} else if(bpp_dst > bpp_src) {
			// perform promotion
			switch(bpp_dst) {
				case 4:
					clone = FreeImage_ConvertTo4Bits(src);
					break;
				case 8:
					clone = FreeImage_ConvertTo8Bits(src);
					break;
				case 16:
					if (isRGB565) {
						clone = FreeImage_ConvertTo16Bits565(src);
					} else {
						// includes case where all the masks are 0
						clone = FreeImage_ConvertTo16Bits555(src);
					}
					break;
				case 24:
					clone = FreeImage_ConvertTo24Bits(src);
					break;
				case 32:
					clone = FreeImage_ConvertTo32Bits(src);
					break;
				default:
					return FALSE;
			}
		} else {
			return FALSE;
		}

		if(!clone) return FALSE;

		// paste src to dst
		switch(FreeImage_GetBPP(dst)) {
			case 1:
				bResult = Combine1(dst, clone, (unsigned)left, (unsigned)top, (unsigned)alpha);
				break;
			case 4:
				bResult = Combine4(dst, clone, (unsigned)left, (unsigned)top, (unsigned)alpha);
				break;
			case 8:
				bResult = Combine8(dst, clone, (unsigned)left, (unsigned)top, (unsigned)alpha);
				break;
			case 16:
				if (isRGB565) {
					bResult = Combine16_565(dst, clone, (unsigned)left, (unsigned)top, (unsigned)alpha);
				} else {
					// includes case where all the masks are 0
					bResult = Combine16_555(dst, clone, (unsigned)left, (unsigned)top, (unsigned)alpha);
				}
				break;
			case 24:
				bResult = Combine24(dst, clone, (unsigned)left, (unsigned)top, (unsigned)alpha);
				break;
			case 32:
				bResult = Combine32(dst, clone, (unsigned)left, (unsigned)top, (unsigned)alpha);
				break;
		}

		if(clone != src)
			FreeImage_Unload(clone);

		}
	else {	// any type other than FITBITMAP
		bResult = CombineSameType(dst, src, (unsigned)left, (unsigned)top);
	}

	return bResult;
}

// ----------------------------------------------------------

/** @brief Creates a dynamic read/write view into a FreeImage bitmap.

 A dynamic view is a FreeImage bitmap with its own width and height, that,
 however, shares its bits with another FreeImage bitmap. Typically, views
 are used to define one or more rectangular sub-images of an existing
 bitmap. All FreeImage operations, like saving, displaying and all the
 toolkit functions, when applied to the view, only affect the view's
 rectangular area.

 Although the view's backing image's bits not need to be copied around,
 which makes the view much faster than similar solutions using
 FreeImage_Copy, a view uses some private memory that needs to be freed by
 calling FreeImage_Unload on the view's handle to prevent memory leaks.

 Only the backing image's pixels are shared by the view. For all other image
 data, notably for the resolution, background color, color palette,
 transparency table and for the ICC profile, the view gets a private copy
 of the data. By default, the backing image's metadata is NOT copied to
 the view.

 As with all FreeImage functions that take a rectangle region, top and left
 positions are included, whereas right and bottom positions are excluded
 from the rectangle area.

 Since the memory block shared by the backing image and the view must start
 at a byte boundary, the value of parameter left must be a multiple of 8
 for 1-bit images and a multiple of 2 for 4-bit images.

 @param dib The FreeImage bitmap on which to create the view.
 @param left The left position of the view's area.
 @param top The top position of the view's area.
 @param right The right position of the view's area.
 @param bottom The bottom position of the view's area.
 @return Returns a handle to the newly created view or NULL if the view
 was not created.
 */
FIBITMAP * DLL_CALLCONV
FreeImage_CreateView(FIBITMAP *dib, unsigned left, unsigned top, unsigned right, unsigned bottom) {
	if (!FreeImage_HasPixels(dib)) {
		return NULL;
	}

	// normalize the rectangle
	if (right < left) {
		INPLACESWAP(left, right);
	}
	if (bottom < top) {
		INPLACESWAP(top, bottom);
	}

	// check the size of the sub image
	unsigned width = FreeImage_GetWidth(dib);
	unsigned height = FreeImage_GetHeight(dib);
	if (left < 0 || right > width || top < 0 || bottom > height) {
		return NULL;
	}

	unsigned bpp = FreeImage_GetBPP(dib);
	uint8_t *bits = FreeImage_GetScanLine(dib, height - bottom);
	switch (bpp) {
		case 1:
			if (left % 8 != 0) {
				// view can only start at a byte boundary
				return NULL;
			}
			bits += (left / 8);
			break;
		case 4:
			if (left % 2 != 0) {
				// view can only start at a byte boundary
				return NULL;
				}
			bits += (left / 2);
			break;
		default:
			bits += left * (bpp / 8);
			break;
	}

	FIBITMAP *dst = FreeImage_AllocateHeaderForBits(bits, FreeImage_GetPitch(dib), FreeImage_GetImageType(dib), 
		right - left, bottom - top, 
		bpp, 
		FreeImage_GetRedMask(dib), FreeImage_GetGreenMask(dib), FreeImage_GetBlueMask(dib));

	if (dst == NULL) {
		return NULL;
	}

	// copy some basic image properties needed for displaying and saving

	// resolution
	FreeImage_SetDotsPerMeterX(dst, FreeImage_GetDotsPerMeterX(dib));
	FreeImage_SetDotsPerMeterY(dst, FreeImage_GetDotsPerMeterY(dib));

	// background color
	FIRGBA8 bkcolor;
	if (FreeImage_GetBackgroundColor(dib, &bkcolor)) {
		FreeImage_SetBackgroundColor(dst, &bkcolor);
	}

	// palette
	memcpy(FreeImage_GetPalette(dst), FreeImage_GetPalette(dib), FreeImage_GetColorsUsed(dib) * sizeof(FIRGBA8));

	// transparency table
	FreeImage_SetTransparencyTable(dst, FreeImage_GetTransparencyTable(dib), FreeImage_GetTransparencyCount(dib));

	// ICC profile
	FIICCPROFILE *src_profile = FreeImage_GetICCProfile(dib);
	FIICCPROFILE *dst_profile = FreeImage_CreateICCProfile(dst, src_profile->data, src_profile->size);
	dst_profile->flags = src_profile->flags;

	return dst;
}
