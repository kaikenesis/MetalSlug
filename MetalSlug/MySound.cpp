#include "framework.h"
#include "MySound.h"

#define SELECT_CHARACTER_BGM "sound/02. Barracks (Character Select).mp3"
#define MISSION1_COAST_BGM "sound/03. Blue Water Fangs -The Island of Dr. Moreau- (Main Theme from METAL SLUG 3) (Stage 1).mp3"
#define ENEMY_SCREAM "sound/metal-slug-fire-scream.mp3"

MCI_OPEN_PARMS openBgm;
MCI_PLAY_PARMS playBgm;
MCI_OPEN_PARMS openScreamSound;
MCI_PLAY_PARMS playScreamSound;

int dwID;

metalSlug::MySound::MySound()
{
	Init();
}

metalSlug::MySound::~MySound()
{
}

void metalSlug::MySound::Init()
{
	dwID = 0;
}

void metalSlug::MySound::PlayingBGM()
{
	switch (GetGameMode()) // 파일 오픈	
	{
	case Title:	openBgm.lpstrElementName = _T(SELECT_CHARACTER_BGM); break;
	case InGame: openBgm.lpstrElementName = _T(MISSION1_COAST_BGM); break;
	}
	openBgm.lpstrDeviceType = _T("mpegvideo");				//mp3 형식
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
	dwID = openBgm.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm); // 음악 반복재생
}

void metalSlug::MySound::PlayingEnemyScream()
{
	openScreamSound.lpstrElementName = _T(ENEMY_SCREAM);
	openScreamSound.lpstrDeviceType = _T("mpegvideo");
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openScreamSound);
	dwID = openScreamSound.wDeviceID;
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openScreamSound);
}
