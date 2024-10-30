#pragma once

namespace metalSlug
{
	class CSoundMgr
	{
	public:
		CSoundMgr();
		~CSoundMgr();

	private:
		LPDIRECTSOUND8	m_pSound;	// 사운드카드 대표 객체
		CSound* m_pBGM;		// 현재 지정된 BGM Sound

	public:
		int init(void);
		LPDIRECTSOUND8 GetSoundDevice() { return m_pSound; }
		void RegisterToBGM(CSound* _pSound);
	};
}
