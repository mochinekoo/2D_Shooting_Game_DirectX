#pragma once
#include <xaudio2.h>
#include <string>
#include <vector>

struct WaveData {
	WAVEFORMATEX waveFormat;
	char* soundBuffer;
	DWORD size;

	~WaveData() { free(soundBuffer); }
};

struct SoundData {
	IXAudio2SourceVoice* sourceVoice = nullptr;
	XAUDIO2_VOICE_STATE state = {};
};

namespace SoundManager {

	inline IXAudio2* xaudio = nullptr;
	inline IXAudio2MasteringVoice* masteringVoice = nullptr;

	inline std::vector<SoundData> audioList;

	HRESULT initialize();
	bool LoadFile(const std::wstring path, WaveData* outData);
	bool Play(const std::wstring& fileName, WaveData* data, bool loop);
	void Stop(int index);
	void Release();

}