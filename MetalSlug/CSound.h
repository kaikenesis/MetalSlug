#pragma once

namespace metalSlug
{
	class CSound
	{
	private:
		LPDIRECTSOUNDBUFFER		m_pSoundBuffer;
		DSBUFFERDESC			m_tBuffInfo;
		int						m_iVolume;

	public:
		int Load(const std::wstring& _strPath);

		// �Ϲ� ���
		void Play(bool _bLoop = false);

		// BGM ���� ���
		void PlayToBGM(bool _bLoop = false);

		void Stop(bool _bReset = false);

		// ���� ���� (0 ~ 100)
		void SetVolume(float _fVolume);

		// �������� ��ġ ����
		void SetPosition(float _fPosition); // 0 ~ 100 ����

	private:
		bool LoadWaveSound(const std::wstring& _strPath);
		int GetDecibel(float _fVolume);

	public:
		CSound();
		virtual ~CSound();
	};
}
