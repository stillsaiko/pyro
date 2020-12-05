// define CINTERFACE
# include <mmdeviceapi.h>
# include <audioclient.h>
// 2.1 -> nChannels == 2
// 5.1 -> nChannels == 6
// 7.1 -> nChannels == 8
# include <cassert>
/*template<class T> class WASAPI // Windows Audio Session API
{
	UINT length = 0;
	BYTE *buffer = nullptr;
	IAudioClient *context = nullptr;
	IAudioRenderClient *service = nullptr;
public:
	static constexpr UINT Z = alignof(T) << 3;
	static constexpr UINT N = sizeof(T) / alignof(T);
	const UINT Hz; // sample rate
	const UINT size = 0; // access
	size_t remain(void){ context->GetBufferSize, context->GetCurrentPadding; }
	void flush(void){ const_cast<UINT &>(size) = 0; }
	~
	WASAPI(void)
	{
		if(buffer)
		{
			assert(length);
			assert(service);
			service->ReleaseBuffer(length, 0);
			assert(format);
			assert(context);
			while(length)
			{
				Sleep(length * 1000 / format->nSamplesPerSec);
				context->GetCurrentPadding(&length);
			}
			context->Stop( );
		}
		if(service) service->Release( ), service = nullptr;
		if(context) context->Release( ), context = nullptr;
		CoUninitialize( );
	}
	WASAPI(size_t buffer, size_t rate = 44100): Hz(0)
	{
		assert(!FAILED(CoInitialize(nullptr)));
		{
			IMMDeviceEnumerator *enumerator = nullptr;
			# pragma warning(suppress: 6031)
			CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
					__uuidof(IMMDeviceEnumerator), (void**)& enumerator);
			// choose device by default
			IMMDevice *device = nullptr;
			assert(enumerator);
			enumerator->GetDefaultAudioEndpoint(eRender, eConsole, & device);
			enumerator->Release( );
			enumerator = nullptr;
			// activate client
			assert(device);
			device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)& context);
			device->Release( );
			device = nullptr;
			// choose shared mix format
			
			WAVEFORMATEXTENSIBLE format
			{
				WAVEFORMATEX
				{
					WAVE_FORMAT_EXTENSIBLE, N, RATE, RATE*sizeof(T),
					sizeof(T), Z, sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX)
				},
				Z,
				SPEAKER_FRONT_LEFT ^ SPEAKER_FRONT_RIGHT
			};
		//	WAVEFORMATEX *format = nullptr;
		//	assert(context);
		//	context->GetMixFormat(& format);
			// initialize client
			assert(format);
			const_cast<UINT &>(Hz) = format->nSamplesPerSec;
			context->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, (samples * 10000000 + Hz - 1) / Hz, 0, format, nullptr);
			assert(sizeof(T) / alignof(T) == format->nChannels);
			CoTaskMemFree(format);
		}
		context->GetService(__uuidof(IAudioRenderClient), (void**)& service);
		// queue zero samples
		service->GetBuffer(Hz, & buffer);
		memset(buffer, 0, sizeof(float) * format->nChannels);
		service->ReleaseBuffer(format->nSamplesPerSec, 0);
		context->Start( );
		// audio loop
		auto dt	= (unique<size_t> % FPS + 1) * Hz / FPS
			- (unique<size_t> % FPS + 0) * Hz / FPS;
		// ...
		service->GetBuffer(dt, & buffer);
		// ...
		if(!SendMessageA(unique<HWND>, WM_APP, (WPARAM)dt, (LPARAM)buffer)) do
		{
			service->ReleaseBuffer(dt, 0);
			++ unique<size_t>;
			Sleep(1000);
			// #@?!
		} while(!SendMessageA(unique<HWND>, WM_APP, (WPARAM)1337, (LPARAM)buffer));
		// ...
		service->GetBuffer(format->nSamplesPerSec, & buffer);
		for(int i=0; i<format->nSamplesPerSec; ++i)
		reinterpret_cast<FLOAT *>(buffer)[i*2+0] = sin(i*0.03),
		reinterpret_cast<FLOAT *>(buffer)[i*2+1] = sin(i*0.03);
		service->ReleaseBuffer(format->nSamplesPerSec, 0);
		Sleep(1000);
		context->Stop( );
		// #@?!
	}
};*/
// WASAPI
template<class> struct AUDCLNT;
template<> struct AUDCLNT<void>
{
	IAudioClient *clnt = nullptr;
	IAudioRenderClient *rdr = nullptr;
protected:
	const size_t rate = 0; // nSamplesPerSec
	const size_t size = 0; // GetBuffer/ReleaseBuffer
	const UINT32 size_max = 0; // GetBufferSize
public:
	static constexpr AUDCLNT_SHAREMODE SHAREMODE = AUDCLNT_SHAREMODE_SHARED;
	static constexpr DWORD STREAMFLAGS = AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM
					^ AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY;
	~
	AUDCLNT(void);
	AUDCLNT(void) = default;
	AUDCLNT(WORD nChannels, DWORD nSamplesPerSec, WORD wBitsPerSample);
	// #@?!
	void *map(UINT32 size); // make sure `size <= margin'
	UINT unmap(void *);
	UINT margin(void); // GetBufferSize - GetCurrentPadding
};
template<class T> struct AUDCLNT : public AUDCLNT<void>
{
	AUDCLNT(void) = default;
	AUDCLNT(DWORD nSamplesPerSec):
	AUDCLNT<void>(sizeof(T) % 3 ? sizeof(T) / alignof(T) : sizeof(T) / 3,
		nSamplesPerSec, sizeof(T) % 3 ? sizeof(T) / 3 << 3  : alignof(T) << 3) { }
	T *map(UINT32 size) { return reinterpret_cast<T *>(AUDCLNT<void>::map(size)); }
	void unmap(T *addr) { AUDCLNT<void>::unmap(addr); }
};
/*
template<class T> struct WASAPI // AUDCLN
{
	static constexpr auto N	= sizeof(T) % 3 ? sizeof(T) / alignof(T) : 3;
	static constexpr auto Z	= sizeof(T) % 3 ? sizeof(T) / 3 : alignof(T);
	static_assert(N <= 2, "please mono or stereo");
	static constexpr GUID SPEAKER = N / 2 ? SPEAKER_FRONT_LEFT ^ SPEAKER_FRONT_RIGHT : SPEAKER_FRONT_CENTER;
	static constexpr DWORD STREAMFLAGS = AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM ^ AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY;
	BYTE *buffer = nullptr;
	UINT samples = 0;
	WAVEFORMATEX *format(DWORD rate)
	{
		static WAVEFORMATEXTENSIBLE EXT;
		EXT.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
		EXT.Format.nChannels = sizeof(T) % 3 ? sizeof(T) / alignof(T) : 3;
		EXT.Format.nSamplesPerSec = rate;
		EXT.Format.nAvgBytesPerSec = sizeof(T) * EXT.Format.nSamplesPerSec;
		EXT.Format.nBlockAlign = sizeof(T);
		EXT.Format.wBitsPerSample = sizeof(T) % 3 ? sizeof(T) / 3 : alignof(T);
		EXT.Format.cbSize = sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX);
		EXT.Samples.wValidBitsPerSample = EXT.Format.wBitsPerSample;
		EXT.dwChannelMask = EXT.Format.nChannels / 2 ? SPEAKER_FRONT_LEFT ^ SPEAKER_FRONT_RIGHT : SPEAKER_FRONT_CENTER;
		return & EXT.Format;
	}
	WASAPI(DWORD rate)
	{
		if(FAILED(CoInitialize(nullptr)))return; // error
		IMMDeviceEnumerator *DE = nullptr;
		# pragma warning(suppress: 6031)
		CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
				__uuidof(IMMDeviceEnumerator), (void**)& DE);
		if(DE == nullptr)return;
		IMMDevice *D = nullptr; // error
		DE->GetDefaultAudioEndpoint(eRender, eConsole, & D);
		DE->Release( );
		DE = nullptr;
		if(D == nullptr)return; // error
		IAudioClient *AC = nullptr;
		D->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)& AC);
		D->Release( );
		D = nullptr;
		if(AC == nullptr)return; // error
		AC->Initialize(AUDCLNT_SHAREMODE_SHARED, STREAMFLAGS, 10000000LL, 0, format(rate), nullptr);
		IAudioRenderClient *ARC = nullptr;
		AC->GetService(__uuidof(IAudioRenderClient), (void**)& ARC);
		if(ARC == nullptr) { AC->Release( ); AC = nullptr; return; } // error
	}
	size_t access(size_t size)
	{
		if(AC == nullptr)return 0; // error
		AC->GetCurrentPadding(&)
		if(ARC == nullptr)return 0; // error
		BYTE *p = nullptr;
		ARC->GetBuffer(samples, & buffer);
		return buffer ? samples : 0; // error
	}
	T & operator[ ](size_t index)
	{
		assert(index < samples);
		return reinterpret_cast<LR *>(buffer)[index];
	}
	size_t flush(void)
	{
		assert(ARC);
		if(auto count = samples)
		return ARC->ReleaseBuffer(count, 0), samples = 0, count;
		return 0;
	}
};*/

///////////////////////////////////////////////////////////////////////////////
/*template<class T> struct WASAPI
{
	IMMDevice* MMD = nullptr;
	IAudioClient* AC = nullptr;
	WAVEFORMATEX* WF = nullptr; // MixFormat
	IAudioRenderClient* ARC = nullptr;
	UINT N = 0;
	BYTE *P = nullptr;
	UINT32 n = 0;



	~
	WASAPI(void)
	{
		CoTaskMemFree(WF);
		CoUninitialize( );
	}
	WASAPI(void) = default;
	WASAPI(HWND H)
	{
		IMMDeviceEnumerator* MMDE = nullptr;

		CoInitialize(nullptr);
		CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
			__uuidof(IMMDeviceEnumerator), reinterpret_cast<void**>(&MMDE));
		MMDE->GetDefaultAudioEndpoint(eRender, eConsole, &MMD);
		MMD->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, reinterpret_cast<void**>(&AC));
		AC->GetMixFormat(&WF);
		if(WF->wFormatTag == WAVE_FORMAT_EXTENSIBLE)
		if(reinterpret_cast<WAVEFORMATEXTENSIBLE*>(WF)->SubFormat == KSDATAFORMAT_SUBTYPE_IEEE_FLOAT)
			MessageBoxA(H, "error: WASAPI IEEE FLOAT", "WASAPI", MB_OK);
		if(WF->wBitsPerSample == 24)
			MessageBoxA(H, "error: WASAPI Z=24", "WASAPI", MB_OK);
		// AC->IsFormatSupported
		AC->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, REFERENCE_TIME( ), 0, WF, nullptr);
		AC->GetBufferSize(&N);
		AC->GetService(__uuidof(IAudioRenderClient), reinterpret_cast<void**>(&ARC));
		// ###############################################################################
		ARC->GetBuffer(N, &P);
		ARC->ReleaseBuffer(N, 0);

		AC->Start( );
		UINT32 CP = 0;
		AC->GetCurrentPadding(&CP);

		ARC->GetBuffer(N - CP, &P);
		ARC->ReleaseBuffer(N - CP, 0);

		AC->Stop( );
	}

	UINT32 map(UINT32 samples = 0xFFFFFFFF)
	{
		UINT32 buf, pad;
		AC->GetBufferSize(&buf);
		AC->GetCurrentPadding(&pad);
		samples = min(samples, buf - pad)
		ARC->GetBuffer(samples, &buffer);
		return samples;
	}
	UINT32 unmap(void)
	{
		ARC->ReleaseBuffer(samples, 0);
	}

	UINT push(BYTE *p)
	{
		BYTE *mem;
		ARC->GetBuffer(n, &mem);
		memcpy(mem, p, n);
		ARC->ReleaseBuffer(n, 0);
		return n;
	}
	UINT32 size(void)
	{
		return AC->GetCurrentPadding(&n), n = N - n;
	}
};*/