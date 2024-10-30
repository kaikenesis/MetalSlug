#pragma once

namespace metalSlug
{
	enum class EBgm
	{
		Select,
		Stage1,
		MAX
	};

	enum class ESfx
	{
		EnemyScream,
		MAX
	};

	class SoundRes
	{
	public:
		SoundRes();
		~SoundRes();


	private:
		// Ű���� �ش� �����θ� �ҷ��� ���� ����
		map<EBgm, class CSound*> bgmRes;
		map<ESfx, class CSound*> sfxRes;
	private:
		void Init();
		void LoadSound(EBgm bgm, std::wstring filePath);
		void LoadSound(ESfx soundEffect, std::wstring filePath);

	public:
		CSound* FindSound(EBgm bgm);
		CSound* FindSound(ESfx soundEffect);
	};
}
