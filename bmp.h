# pragma once
# include <cstdint>
# include "rc.h"
//////////////////////////////////////////////////////////////////////////
# ifdef _WIN32 // windows
# define WIN32_LEAN_AND_MEAN
# include <windows.h> // BITMAPINFO
# endif
//////////////////////////////////////////////////////////////////////////
template<class> struct BI;
template<>
struct BI<void> // BITMAPCOREHEADER
{
	unsigned size = sizeof(BI<void>);
	int width, height;
	unsigned short planes = 1, bit_count;
//	unsigned compression, size_image = 0;
//	int x_pels_per_meter = 0, y_pels_per_meter = 0;
//	unsigned clr_used = 0, clr_important = 0;
	unsigned colors[256];
	BI(RC&&);
};
template<class T>
struct BI :
public BI<void>
{
	BI(RC&&RC): BI<void>(std::move(RC)) { }
};
//////////////////////////////////////////////////////////////////////////
/*struct BM : RC
{
	struct bmiHeader
	{
		uint32_t biSize = sizeof(bmiHeader);
		 int32_t biWidth;
		 int32_t biHeight;
		uint16_t biPlanes = 1;
		uint16_t biBitCount;
		uint32_t biCompression;
		uint32_t biSizeImage = 0;
		 int32_t biXPelsPerMeter = 0;
		 int32_t biYPelsPerMeter = 0;
		uint32_t biClrUsed = 0;
		uint32_t biClrImportant = 0;
	};
	const uint32_t * const bmiColors = nullptr;
	enum {AUTO, PAL8, BGR16, BGR24, BGRA32} const type = AUTO;
	~
	BM(void)noexcept;
	BM(void)noexcept;
	BM(RC &&);
	// move semantics
	void operator = (BM &&)noexcept;
	// BITMAPINFOHEADER @#?!
	const bmiHeader	* operator ->(void);
	const void	* operator[ ](size_t);
	// ...
# ifdef _WIN32 // CreateDIBSection
	static_assert(sizeof(bmiHeader) == sizeof(BITMAPINFOHEADER), "@#?!");
	operator const BITMAPINFO *(void);
# endif
};*/
struct BM
{
	enum Z {X1=1, X4=4, X8=8, X1R5G5B5=16, R8G8B8=24, X8R8G8B8=32};
//static constexpr uint32_t B4G4R4[ ]{0x00000F00, 0x000000F0, 0x0000000F};
//static constexpr uint32_t B5G5R5[ ]{0x00007C00, 0x000003E0, 0x0000001F};
//static constexpr uint32_t B5G6R5[ ]{0x0000F800, 0x000007E0, 0x0000001F};
//static constexpr uint32_t B8G8R8[ ]{0x00FF0000, 0x0000FF00, 0x000000FF};
# ifdef _WIN32 // CreateDIBSection
	operator const BITMAPINFO *(void);
# endif
protected:
	uint32_t biSize = sizeof(BM);
	 int32_t biWidth;
	 int32_t biHeight;
	uint16_t biPlanes = 1;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage = 0;
	 int32_t biXPelsPerMeter = 0;
	 int32_t biYPelsPerMeter = 0;
	uint32_t biClrUsed = 0;
	uint32_t biClrImportant = 0;
};
//////////////////////////////////////////////////////////////////////////
# include <memory> // std::move
struct BGR { uint8_t B, G, R; };
// 24 bpp must be stored in BGR format
template<class T = BGR> struct BMP;
//////////////////////////////////////////////////////////////////////////
template<> class BMP<void> : protected BM//::bmiHeader
{
protected:
	uint32_t bmiColors[256] {0};
	uint32_t *buffer = nullptr;
	uint32_t stride = 0; // NEW
public:
	const int32_t X, const Y;
	const uint16_t Z = 24; // bpp
	~
	BMP(void)noexcept;
	BMP(void)noexcept;
	BMP(RC &&, BM::Z explicit_bit_depth = static_cast<BM::Z>(0));
	BMP(int32_t, int32_t, BM::Z, const void * = nullptr);
	void * operator[ ](int32_t);
};
//////////////////////////////////////////////////////////////////////////
// X4R4G4B4: 0x00000F00, 0x000000F0, 0x0000000F
// X1R5G5B5: 0x00007C00, 0x000003E0, 0x0000001F
//   R5G6B5: 0x0000F800, 0x000007E0, 0x0000001F
//   R8G8B8: 0x00FF0000, 0x0000FF00, 0x000000FF
// X8R8G8B8: 0x00FF0000, 0x0000FF00, 0x000000FF
enum
{	// 16 Bit
	X1R5G5B5,
	A1R5G5B5,
	R5G6B5,
	X4R4G4B4,
	A4R4G4B4,
	// 24 Bit
	R8G8B8,
	// 32 Bit
	X8R8G8B8,
	A8R8G8B8
};
/*template<size_t> struct M { };
template<> struct M<2>
{
	static constexpr uint32_t R = 0x7C00;
	static constexpr uint32_t G = 0x03E0;
	static constexpr uint32_t B = 0x001F;
};
template<> struct M<3>
{
	static constexpr uint32_t R = 0xFF0000;
	static constexpr uint32_t G = 0x00FF00;
	static constexpr uint32_t B = 0x0000FF;
};
template<> struct M<4>
{
	static constexpr uint32_t R = 0x00FF0000;
	static constexpr uint32_t G = 0x0000FF00;
	static constexpr uint32_t B = 0x000000FF;
	static constexpr uint32_t A = 0xFF000000;
};*/
template<class T>
struct BMP :
public BMP<void>
{
	BMP(void)noexcept
	{ }
	BMP(RC &&RC):
	BMP<void>(std::move(RC), static_cast<decltype(BM::BGR8)>(sizeof(T)))
	{ }
	T * operator[ ](size_t i)
	{
		return reinterpret_cast<T *>( BMP<void>::operator[ ](i) );
	}
};
//////////////////////////////////////////////////////////////////////////