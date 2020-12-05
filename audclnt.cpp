# include "audclnt.h"
AUDCLNT<void>::~AUDCLNT(void)
{
	if(rdr) rdr->Release( ), rdr = nullptr;
	if(clnt) clnt->Stop( ), clnt->Release( ), clnt = nullptr, CoUninitialize( );
}
AUDCLNT<void>::AUDCLNT(WORD nChannels, DWORD nSamplesPerSec, WORD wBitsPerSample): rate(nSamplesPerSec), size(0), size_max(0)
{
	DWORD dwChannelMask = nChannels < 2 ? SPEAKER_FRONT_CENTER
			: SPEAKER_FRONT_LEFT ^ SPEAKER_FRONT_RIGHT;

	if(FAILED(CoInitialize(nullptr)))return; // error
	IMMDeviceEnumerator *enumerator = nullptr;
	# pragma warning(suppress: 6031)
	CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL,
			__uuidof(IMMDeviceEnumerator), (void**)& enumerator);
	if(enumerator == nullptr)return;
	// choose device by default
	IMMDevice *device = nullptr; // error
	enumerator->GetDefaultAudioEndpoint(eRender, eConsole, & device);
	enumerator->Release( );
	enumerator = nullptr;
	if(device == nullptr)return; // error
	// activate client
	device->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)& clnt);
	device->Release( );
	device = nullptr;
	if(clnt == nullptr)return; // error
	// choose shared mix format
	WAVEFORMATEXTENSIBLE EXT;
	EXT.Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
	EXT.Format.nChannels = nChannels;
	EXT.Format.nSamplesPerSec = nSamplesPerSec;
	EXT.Format.nAvgBytesPerSec = nChannels * wBitsPerSample * nSamplesPerSec / CHAR_BIT;
	EXT.Format.nBlockAlign = nChannels * wBitsPerSample / CHAR_BIT;
	EXT.Format.wBitsPerSample = wBitsPerSample;
	EXT.Format.cbSize = sizeof(WAVEFORMATEXTENSIBLE) - sizeof(WAVEFORMATEX);
	EXT.Samples.wValidBitsPerSample = wBitsPerSample;
	EXT.dwChannelMask = dwChannelMask;
	// initialize client
	clnt->Initialize(SHAREMODE, STREAMFLAGS, 10000000LL, 0, & EXT.Format, nullptr);
	clnt->GetBufferSize(&const_cast<UINT32 &>(size_max));
	clnt->GetService(__uuidof(IAudioRenderClient), (void**)& rdr);
	if(rdr == nullptr) { clnt->Release( ); clnt = nullptr; return; } // error
	// queue zero samples
	BYTE *buffer = nullptr;
	rdr->GetBuffer(nSamplesPerSec, & buffer);
	memset(buffer, 0, nChannels * wBitsPerSample / CHAR_BIT);
	rdr->ReleaseBuffer(nSamplesPerSec, 0);
	clnt->Start( );
}
void *AUDCLNT<void>::map(UINT32 size)
{
	BYTE *buffer = nullptr;
	if(rdr && !size) rdr->GetBuffer(const_cast<UINT32 &>(size) = size, & buffer);
	return buffer;
}
UINT AUDCLNT<void>::unmap(void *)
{
	if(rdr) if(auto size = this->size)
	return rdr->ReleaseBuffer(size, 0), const_cast<UINT32 &>(size) = 0, size;
	return 0;
}
UINT AUDCLNT<void>::margin(void)
{
	if(clnt == nullptr)return 0;
	UINT padding = 0;
	clnt->GetCurrentPadding(& padding);
	return size_max - padding;
}