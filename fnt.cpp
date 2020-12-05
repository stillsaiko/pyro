// Microsoft Windows Reference Manual [425, 431]

// C.1 Introduction
// The standard FONTS .FON file provided with Windows includes fonts for both 2:1 and 1:1 aspect ratio displays and only the fonts whose aspect ratio matches the display are actually used. There are three sizes of fonts provided in the ANSI character set: 6, 8, and 11 pixels high for 2:1 displays and 12, 16, and 22 pixels high for 1:1 displays. There is only one 1:1 and one 2:1 OEM-dependent font. There are both Terminal and Document faces in each size.
// Windows is capable of synthesizing attributes, such as bold, italic, and underlined, so such fonts are not in FONTS.FON. The fonts that do not correspond to the user's display aspect ratio are nevertheless generic raster fonts that can be used for output devices such as bitmap printers.

// C.2 Font File Formats
// Formats for font files are defined for both raster and vector fonts. These formats may be used by smart text generators in some GDI support modules. The vector formats, in particular, are more frequently used by GDI itself than by support modules.
// Both types of files begin with information which is colhmon to both, and then continue with information which differs for each type of file. Font files are stored with a .fnt extension of the form name.fnt. The information at the beginning of both types of files is as follows:
struct __FNT__
{
	char dfVersion[2]; // WORD specifying the version of the file (currently 256).
	char dfSize[4]; // DWORD specifying the total file size in bytes.
	char dfCopyright[60]; // CHAR[60] specifying copyright information.
	char dfType[2]; // WORD specifying the type of font file. The low-order byte is for exclusive GDI use. If the low-order bit of the word is 0, it is a bitmap (rastor) font file. If the low-order bit is 1, it is a vector font file. The second bit is reserved and must be zero. If no bits follow in the file and the bits are located in memory at a fixed address specified in dfBitsOffset, the third bit is set to 1; otherwise, the bit is set to 0. The high bit of the low-order byte is set if the font was realized by a device. The remaining bits in the low-order byte are reserved and set to zero.
	// The high-order byte is reserved for device use and will always be set to zero for GDI realized standard fonts. Physical fonts with the high bit of the low-order byte set may use this byte to describe themselves. GDI will never inspect the high-order byte.
	char dfPoints[2]; // WORD specifying the nominal point size at which this character set looks best.
	char dfVertRes[2]; // WORD specifying the nominal vertical resolution (dots per inch) at which this character set was digitized.
	char dfHorizRes[2]; // WORD specifying the nominal horizontal resolution (dots per inch) at which this character set was digitized.
	char dfAscent[2]; // WORD specifying the distance from the top of a character definition cell to the baseline of the typographical font. It is useful for aligning the b aseline of fonts of different heights.
	char dfIternalLeading[2]; // WORD specifying the amount of leading inside the bounds set by dfPixHeight. Accent marks may occur in this area. This may be zero at the designer's option.
	char dfExternalLeading[2]; // WORD specifying the amount of extra leading that the designer requests the application add between rows. Since this area is outside of the font proper, it contains no marks, and will not be altered by text output calls in either OPAQUE or TRANSPARENT mode. This may be zero at the designer's option.
	char dfltalic; // BYTE specifying whether the character definition data represent an italic font. The low-order bit is one if the flag is set. All other bits are zero.
	char dfUnderline; // BYTE specifying whether the character definition data represent an underlined font. The low-order bit is one if the flag is set. All other bits are zero. 
	char dfStrikeOut; // BYTE specifying whether the character definition data represent a strikeout font. The low-order bit is one if the flag is set. All other bits are zero.
	char dfWeight[2]; // WORD specifying the weight of the characters in the character definition data, on a scale from 1-1000. A weight of 100 is the usual for light type, 200 specifies regular, 300 semibold, and so forth.
	char dfCharSet; // BYTE specifying the character set defined by this font. The IBM@ PC hardware font has been assigned the designation 377 octal (FF hexadecimal or 255 decimal).
	char dfPixWidth[2]; // WORD. For vector fonts, specifies the width of the grid on which the font was digitized. For raster fonts, if dfPix Width is nonzero, it represents the width for all characters in the bitmap; if it is zero, the font has variable width characters whose widths are specified in the dfCharOffset array.
	char dfPixHeight[2]; // WORD specifying the height of the character bitmap (raster fonts), or the height of the grid on which a vector font was digitized.
	char dfPitchAndFamily; // Specifies the pitch and font family. The low bit is set if the font is variable-pitch. The four high-order bits give the family name of the font. The values are:
	// FF_DONTCARE (0<<4)
	// FF_ROMAN (1<<4)
	// FF_SWISS (2<<4)
	// FF_MODERN (3<<4)
	// FF_SCRIPT (4<<4)
	// FF_DECORATIVE (5<<4)
	// Font families describe in a general way the look of a font. They are intended for specifying fonts when the exact facename desired is not available. The families are:
	// FF_DONTCARE Don't care or don't know.
	// FF_ROMAN Fonts with variable stroke width, serifed. Times Roman, Century Schoolbook, etc.
	// FF_SWISS Fonts with variable stroke width, sans-serifed. Helvetica, Swiss, etc.
	// FF_MODERN Fonts with constant stroke width, serifed or sans-serifed. Fixed-pitch fonts are usually modern. Pica, Elite, Courier, etc.
	// FF_SCRIPT Cursive, etc.
	// FF_DECORATIVE Old English, etc.
	char dfAvgWidth[2]; // WORD specifying the width of characters in the font. For fixed-pitch fonts this is the same as dfPix Width. For variable-pitch fonts this is the width of the character 'X'. 
	char dfMaxWidth[2]; // WORD specifying the maximum pixel width of any character in the font. For fixed-pitch fonts, this is simply dfPix Width.
	char dfFirstChar; // BYTE specifying the first character code defined by this font. Character definitions are stored only for the characters actually present in a font, so use this field when calculating indexes into either dfBits or dfCharOffset.
	char dfLastChar; // BYTE specifying the last character code defined by this font. Note that all characters with codes between dfFirstChar and dfLastChar must be present in the font character definitions.
	char dfDefaultChar; // BYTE specifying the character to substitute whenever a string contains a character out of the range dfFirstChar through dfLastChar. The character is given relative to dfFirstChar so that dfDefaultChar is the actual value of the character less dfFirstChar. dfDefaultChar should indicate a special character in the font which is not a space.
	char dfBreakChar; // BYTE specifying the character that will define word breaks. This character defines word breaks for word wrapping and word spacing justification. The character is given relative to dfFirstChar so that dfBreakChar is the actual value of the character less dfFirstChar. dfBreakChar is normally (32 - dfFirstChar), which is an ASCII space.
	char dfWidthBytes[2]; // WORD specifying the number of bytes in each row of the bitmap (raster fonts). No meaning for vector fonts. dfWidthBytes is always an even quantity so that rows of the bitmap start on word boundaries.
	char dfDevice[4]; // DWORD specifying the offset in the file to the string giving the device name. For a generic device, this value will be zero (0).
	char dfFace[4]; // DWORD specifying the offset in the file to the null-terminated string that names the face.
	char dfBitsPointer[4]; // DWORD specifying the absolute machine address of the bitmap. This is set by GDI at load time. dfBitsPointer is guaranteed to be even.
	char dfBitsOffset[4]; // DWORD specifying the offset in the file to the beginning of the bitmap information. If the 04h bit in dfType is set, then dfBitsOffset is an absolute address of the bitmap. (Probably in ROM) For raster fonts, it points to a sequence of bytes that makes up the bitmap of the font, whose height is the height of the font, and whose width is the sum of the widths of the characters in the font rounded up to the next word boundary. For vector fonts, it points to a string of bytes or words (depending on the size of the grid on which the font was digitized) specifying the strokes for each character of the font. dfBitsOffset must be even.
/////////////////////////////////
	char dfReserved; // BYTE, not used.
	char dfFlags[4]; // DWORD specifying the bits flags, which are additional flags that define the format of the Glyph bitmap, as follows:
	// DFF_FIXED            equ  0001h ; font is fixed pitch
	// DFF_PROPORTIONAL     equ  0002h ; font is proportional pitch
	// DFF_ABCFIXED         equ  0004h ; font is an ABC fixed font
	// DFF_ABCPROPORTIONAL  equ  0008h ; font is an ABC proportional font
	// DFF_1COLOR           equ  0010h ; font is one color
	// DFF_16COLOR          equ  0020h ; font is 16 color
	// DFF_256COLOR         equ  0040h ; font is 256 color
	// DFF_RGBCOLOR         equ  0080h ; font is RGB color
	char dfAspace[2]; // WORD specifying the global A space, if any. The dfAspace is the distance from the current position to the left edge of the bitmap.
	char dfBspace[2]; // WORD specifying the global B space, if any. The dfBspace is the width of the character.
	char dfCspace[2]; // WORD specifying the global C space, if any. The dfCspace is the distance from the right edge of the bitmap to the new current position. The increment of a character is the sum of the three spaces. These apply to all glyphs and is the case for DFF_ABCFIXED.
	char dfColorPointer[4]; // DWORD specifying the offset to the color table for color fonts, if any. The format of the bits is similar to a DIB, but without the header. That is, the characters are not split up into disjoint bytes. Instead, they are left intact. If no color table is needed, this entry is NULL.
	// [NOTE: This information is different from that in the hard-copy Developer's Notes and reflects a correction.]
	char dfReserved1[16]; // BYTE[16], not used.
	// [NOTE: This information is different from that in the hard-copy Developer's Notes and reflects a correction.]
	char dfCharTable[1536]; // For raster fonts, the CharTable is an array of entries each consisting of two 2-byte WORDs for Windows 2.x and three 2-byte WORDs for Windows 3.0. The first WORD of each entry is the character width. The second WORD of each entry is the byte offset from the beginning of the FONTINFO structure to the character bitmap. For Windows 3.0, the second and third WORDs are used for the offset.
	// There is one extra entry at the end of this table that describes an absolute-space character. This entry corresponds to a character that is guaranteed to be blank; this character is not part of the normal character set.
	// The number of entries in the table is calculated as ((dfLastChar - dfFirstChar) + 2). This includes a spare, the sentinel offset mentioned in the following paragraph.
	// For fixed-pitch vector fonts, each 2-byte entry in this array specifies the offset from the start of the bitmap to the beginning of the string of stroke specification units for the character. The number of bytes or WORDs to be used for a particular character is calculated by subtracting its entry from the next one, so that there is a sentinel at the end of the array of values.
	// For proportionally spaced vector fonts, each 4-byte entry is divided into two 2-byte fields. The first field gives the starting offset from the start of the bitmap of the character strokes. The second field gives the pixel width of the character.
	
/////////////////////////////////
//	char dfCharOffset[2]; // For proportionally spaced raster fonts, this field contains two bytes giving the offset from the start of each bitmap row for each character in the set. The number of characters present in the set is calculated as (dfLastChar-dfFirstChar)+1) and one spare, used for the sentinel offset. The total is therefore (( dfLastChar-dfFirstChar)+2) entries, each of two bytes. For equal-width raster fonts, this field collapses to zero size because all widths may be obtained by looking up the width in dJPix Width.
	// For fixed-pitch vector fonts, each two-byte entry in this array specifies the offset from the start of the bitmap to the beginning of the string of stroke-specification units for the character. The number of bytes or words to be used for a particular character is calculated in the same fashion as the width of a raster character (i.e. , subtract its entry from the next one), so that both types of font require a sentinel value at the end of the array of values.
	// For proportionally spaced vector fonts, each four-byte entry is divided into two two-byte fields. The first field gives the starting offset from Lhe start of the bitmap of the character strokes as for fixed-pitch fonts. The second field gives the pixel width of the character.
//	char *facename; // An ASCII character string specifying the name of the font face. The size of this field is the length of the string plus a null terminator.
//	char *devicename; // An ASCII character string specifying the name of the device if this font file is for a specific device. The size of this field is the length of the string plus a null terminator.
//	void *bitmaps; // This field contains the bitmap definitions. The size of this field depends on the length of the bitmap definitions. Each row of a raster bitmap must start on a word boundary. This implies that the end of each row must be padded to an even length.
};

// C.2.1 Raster Font File Format
// In addition to the information in the header to the file, a raster font file contains a string of bytes which is the actual bitmap, just as it will be loaded into contiguous memory. That string begins in the file at the offset specified in the jiBits field above.

// C.2.2 Vector Font File Format
// The header information for a vector font file is as described in Section C.2, "Font File Formats." This section describes some additional information for vector font files.
// The CharOffset field is used to specify the location and usage of the character strokes in the bitmap area. For fixed-pitch fonts, each two-byte entry is an offset from the start of the bitmap to the beginning of the strokes for the character. For variable-pitch fonts, each four-byte entry consists of two bytes giving the offset (as for fixed-pitch) and two bytes giving the width of the character.
// For both fixed- and variable- pitch fonts, the bitmap area is the same. Each character is composed of a series of vectors consisting of a pair of signed relative coordinate pairs starting from the character cell origin. Each pair may be preceded by a special value indicating that the next coordinate is to be a pen-up move. The special pen-up value depends on how the coordinates are stored. For one-byte quantities, it is -128 (080H) and for two-byte quantities, it is -32768 (08000H).
// The character cell origin must be at the upper left corner of the cell so that the character hangs down and to the right of where it is placed.
// The storage format for the coordinates depends on the size of the font. If either dfPixHeight or dfMax Width is greater than 128, the coordinates are stored as 2-byte quantities; otherwise, they are stored as 1-byte quantities.
//////////////////////////////////////////////////////////////////////////////
// fon.cpp
//////////////////////////////////////////////////////////////////////////////
# include "fnt.h"
FNT::FNT(void)
{ }
# include <memory>
# include <cassert>
FNT::FNT(RC && a): rc(std::move(a))
{
sizeof(__FNT__);
	if(rc[0] == 'M' && rc[1] == 'Z')
	{
		// not yet supported
	}
	else
	{
		const auto & fnt = reinterpret_cast<const __FNT__ &>(rc[0]);
		assert( *(WORD*)fnt.dfVersion == 0x0300);
		printf("%u dfSize\n", *(DWORD*)fnt.dfSize);
		printf("warning: FNT %*s\n", 60, fnt.dfCopyright);
		if(auto type = *(WORD*)fnt.dfType)
		{
			printf("warning: FNT dfType should be 0 and not %hu\n", type);
		}
		printf("%hu dfPoints\n", *(WORD*)fnt.dfPoints);
		printf("%hu dfVertRes\n", *(WORD*)fnt.dfVertRes);
		printf("%hu dfHorizRes\n", *(WORD*)fnt.dfHorizRes);
		printf("%hu dfAscent\n", *(WORD*)fnt.dfAscent);
		if( *(WORD*)fnt.dfIternalLeading || *(WORD*)fnt.dfExternalLeading )
		{
			printf("warning: FNT dfIternalLeading, dfExternalLeading should be 0\n");
		}
		if( fnt.dfltalic || fnt.dfUnderline || fnt.dfStrikeOut )
		{
			printf("warning: FNT dfltalic, dfUnderline, dfStrikeOut should be 0\n");
		}
		if(auto weight = *(WORD*)fnt.dfWeight; weight != 400)
		{
			printf("warning: FNT dfWeight should be 400 and not %hu\n", weight);
		}
		if(auto charset = fnt.dfCharSet; charset != 2)
		{
			printf("warning: FNT dfWeight should be 2 and not %hu\n", charset);
		}
		printf("%hu dfPixWidth\n", *(WORD*)fnt.dfPixWidth);
		printf("%hu dfPixHeight\n", *(WORD*)fnt.dfPixHeight);
		if(fnt.dfPitchAndFamily != FF_DONTCARE)
		{
			printf("warning: FNT dfPitchAndFamily FF_DONTCARE\n");
		}
		printf("%hu dfAvgWidth\n", *(WORD*)fnt.dfAvgWidth);
		printf("%hu dfMaxWidth\n", *(WORD*)fnt.dfMaxWidth);
		printf("%hhu dfFirstChar\n", fnt.dfFirstChar);
		printf("%hhu dfLastChar\n", fnt.dfLastChar);
		printf("%hhu dfDefaultChar\n", fnt.dfDefaultChar);
		printf("%hhu dfBreakChar\n", fnt.dfBreakChar);
		printf("%hu dfWidthBytes\n", *(WORD*)fnt.dfWidthBytes);
		if(auto device = *(DWORD*)fnt.dfDevice)
		{
			printf("warning: FNT dfDevice should be 0 and not %u\n", device);
		}
		printf("%s dfFace\n", &rc[*(DWORD*)fnt.dfFace]);
		if(auto bitptr = *(DWORD*)fnt.dfBitsPointer)
		{
			printf("warning: FNT dfBitsPointer should be 0 and not %u\n", bitptr);
		}
		printf("%u dfBitsOffset\n", *(DWORD*)fnt.dfBitsOffset);
		printf("%hhu dfReserved\n", fnt.dfReserved);
		for(WORD i = *(BYTE*)&fnt.dfFirstChar; i <= (WORD)*(BYTE*)&fnt.dfLastChar+1; ++i)
			printf("dfCharTable[%hu] %hu %u\n", i,
				*(WORD*)&fnt.dfCharTable[(i-*(BYTE*)&fnt.dfFirstChar)*6],
				*(DWORD*)&fnt.dfCharTable[(i-*(BYTE*)&fnt.dfFirstChar)*6+2]);
		////////////////////////////
# define DFF_FIXED		0x0001
# define DFF_PROPORTIONAL	0x0002
# define DFF_ABCFIXED		0x0004
# define DFF_ABCPROPORTIONAL	0x0008
# define DFF_1COLOR		0x0010
# define DFF_16COLOR		0x0020
# define DFF_256COLOR		0x0040
# define DFF_RGBCOLOR		0x0080
		const DWORD& dfFlags = *reinterpret_cast<const DWORD *>(fnt.dfFlags);
		assert(dfFlags & DFF_ABCFIXED || dfFlags & DFF_ABCPROPORTIONAL ? false : true);
/*		switch(dfFlags & 0x00F0)
		{
			case DFF_1COLOR:
			case DFF_16COLOR:
			case DFF_256COLOR:
			case DFF_RGBCOLOR:
			default:
				assert(false);
		}*/
		assert( *(DWORD*)fnt.dfFlags == DFF_FIXED );
		assert( !*(WORD*)fnt.dfAspace );
		assert( !*(WORD*)fnt.dfBspace );
		assert( !*(WORD*)fnt.dfCspace );
		assert( !*(DWORD*)fnt.dfColorPointer );
		////////////////////////////
	//	printf("%hu dfCharOffset\n", *(WORD*)fnt.dfCharOffset);
		// facename
		// devicename
		// bitmaps
	}
/*
	// load RC
	int cHeight, cWidth, cEscapement, cOrientation, cWeight;
	DWORD bItalic, bUnderline, bStrikeout, iCharset, iOutPrecision, iClipPrecision, iQuality, iPitchAndFamily;
	LPCSTR pszFaceName = "saiko";
	H = CreateFontA(cHeight, cWidth, cEscapement, cOrientation, cWeight, bItalic, bUnderline, bStrikeout, iCharset, iOutPrecision,
	iClipPrecision, iQuality, iPitchAndFamily, pszFaceName);*/
}
// SelectObject youwself
void FNT::operator = (FNT && a)noexcept
{
	rc = std::move(a.rc);
}
const char * FNT::operator[ ](char a)
{
	struct GlyphEntry
	{
		WORD size;
		WORD offs[2];
	};
	const auto & fnt = reinterpret_cast<const __FNT__ &>(rc[0]);
	return & rc[ *(DWORD*)reinterpret_cast<const GlyphEntry *>(fnt.dfCharTable)[a - fnt.dfFirstChar].offs ];
}