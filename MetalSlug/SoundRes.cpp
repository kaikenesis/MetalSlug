#include "framework.h"
#include "SoundRes.h"

metalSlug::SoundRes::SoundRes()
{
	Init();
}

metalSlug::SoundRes::~SoundRes()
{
}

void metalSlug::SoundRes::Init()
{
	//BGM
	LoadSound(EBgm::Select, _T("sound/02.-Barracks-_Character-Select__1.wav"));
	LoadSound(EBgm::Stage1, _T("sound/03.-Blue-Water-Fangs-The-Island-of-Dr.-Moreau-_Main-Theme-from-METAL-SLUG-3_-_Stage-1__1.wav"));

	//SoundEffect
	LoadSound(ESfx::EnemyScream, _T("sound/metal-slug-fire-scream_1.wav"));
}

void metalSlug::SoundRes::LoadSound(EBgm bgm, std::wstring filePath)
{
	CSound* sound = new CSound();
	sound->Load(filePath);
	bgmRes.insert(pair<EBgm, CSound*>(bgm, sound));
}

void metalSlug::SoundRes::LoadSound(ESfx soundEffect, std::wstring filePath)
{
	CSound* sound = new CSound();
	sound->Load(filePath);
	sfxRes.insert(pair<ESfx, CSound*>(soundEffect, sound));
}

CSound* metalSlug::SoundRes::FindSound(EBgm bgm)
{
	return bgmRes.find(bgm)->second;
}

CSound* metalSlug::SoundRes::FindSound(ESfx soundEffect)
{
	return sfxRes.find(soundEffect)->second;
}
