#include "SoundManager.h"
#pragma comment(lib, "xaudio2.lib")
#include <xaudio2.h>
#include <assert.h>
#include <string>
#pragma comment ( lib, "winmm.lib" )


HRESULT SoundManager::initialize() {
    HRESULT result;
    result = XAudio2Create(&xaudio);
    assert(SUCCEEDED(result));
    result = xaudio->CreateMasteringVoice(&masteringVoice);
    assert(SUCCEEDED(result));
    return result;
}

bool SoundManager::LoadFile(const std::wstring path, WaveData* outData) {
    HMMIO mmio = nullptr;
    MMCKINFO chunkInfo = {};
    MMCKINFO riffChunkInfo = {};
    mmio = mmioOpen(
        (LPWSTR) path.data(),
        nullptr,
        MMIO_READ
    );
    if (!mmio) {
        return false;
    }
    riffChunkInfo.fccType = mmioFOURCC('W', 'A', 'V', 'E');

    if (mmioDescend(
        mmio,
        &riffChunkInfo,
        nullptr,
        MMIO_FINDRIFF
    ) != MMSYSERR_NOERROR){
        mmioClose(mmio, MMIO_FHOPEN);
        return false;
    }

    chunkInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');

    if (mmioDescend(
        mmio,
        &chunkInfo,
        &riffChunkInfo,
        MMIO_FINDCHUNK
    ) != MMSYSERR_NOERROR) {
        mmioClose(mmio, MMIO_FHOPEN);
        return false;
    }

    DWORD readSize = mmioRead(
        mmio,
        (HPSTR)&outData->waveFormat,
        chunkInfo.cksize
    );

    if (readSize != chunkInfo.cksize) {
        mmioClose(mmio, MMIO_FHOPEN);
        return false;
    }

    if (outData->waveFormat.wFormatTag != WAVE_FORMAT_PCM) {
        mmioClose(mmio, MMIO_FHOPEN);
        return false;
    }

    if (mmioAscend(mmio, &chunkInfo, 0) != MMSYSERR_NOERROR) {
        mmioClose(mmio, MMIO_FHOPEN);
        return false;
    }

    chunkInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
    if (mmioDescend(mmio, &chunkInfo, &riffChunkInfo, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {
        mmioClose(mmio, MMIO_FHOPEN);
        return false;
    }

    outData->size = chunkInfo.cksize;

    outData->soundBuffer = new char[chunkInfo.cksize];
    readSize = mmioRead(mmio, (HPSTR)outData->soundBuffer, chunkInfo.cksize);
    if (readSize != chunkInfo.cksize) {
        mmioClose(mmio, MMIO_FHOPEN);
        delete[] outData->soundBuffer;
        return false;
    }

    return true;
}

bool SoundManager::Play(const std::wstring& fileName, WaveData* data, bool loop) {
    if (!LoadFile(fileName, data)) {
        return false;
    }
    WAVEFORMATEX waveFormat = {};
    memcpy_s(&waveFormat, sizeof(WAVEFORMATEX), &data->waveFormat, sizeof(data->waveFormat));
    waveFormat.wBitsPerSample = data->waveFormat.nBlockAlign * 8 / data->waveFormat.nChannels;
    SoundData soundData = {};
    HRESULT result = xaudio->CreateSourceVoice(&soundData.sourceVoice, (WAVEFORMATEX*) &waveFormat);
    assert(SUCCEEDED(result));

    XAUDIO2_BUFFER xAudio2Buffer = {};
    xAudio2Buffer.pAudioData = (BYTE*)data->soundBuffer;
    xAudio2Buffer.Flags = XAUDIO2_END_OF_STREAM;
    xAudio2Buffer.AudioBytes = data->size;

    xAudio2Buffer.LoopCount = loop ? XAUDIO2_LOOP_INFINITE : 0;
    soundData.sourceVoice->SubmitSourceBuffer(&xAudio2Buffer);

    result = soundData.sourceVoice->Start();
    assert(SUCCEEDED(result));

    audioList.push_back(soundData);
    return true;
}

void SoundManager::Stop(int index) {
    audioList[index].sourceVoice->Stop();
    audioList[index].sourceVoice->FlushSourceBuffers();
}

void SoundManager::Release()
{
}
