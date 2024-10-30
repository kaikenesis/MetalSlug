#pragma once

namespace metalSlug
{
	class CSoundMgr
	{
	public:
		CSoundMgr();
		~CSoundMgr();

	private:
		LPDIRECTSOUND8	m_pSound;	// ����ī�� ��ǥ ��ü
		CSound* m_pBGM;		// ���� ������ BGM Sound

	public:
		int init(void);
		LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
		void RegisterToBGM(CSound* _pSound);
	};
}
