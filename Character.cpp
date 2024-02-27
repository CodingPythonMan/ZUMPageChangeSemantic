#include "Character.h"

std::map<unsigned int, Character*> gCharacterMap;

// 월드맵 캐릭터 섹터
std::list<Character*> gSector[dfSECTOR_MAX_Y][dfSECTOR_MAX_X];

//int Temp = 0;

Character::Character(Session* sessionPtr, unsigned int sessionID)
{
	SessionPtr = sessionPtr;
	SessionID = sessionID;
	Action = dfPACKET_MOVE_DIR_LL;
	Direct = dfPACKET_MOVE_DIR_LL;
	MoveDirect = dfPACKET_MOVE_STOP;
	X = rand() % dfRANGE_MOVE_RIGHT;
	Y = rand() % dfRANGE_MOVE_BOTTOM;

	/*
	if (Temp == 0)
	{
		X = 6300;
		Y = 6300;
		Temp++;
	}
	else if (Temp == 1)
	{
		X = 6250;
		Y = 6250;
		Temp++;
	}
	else if (Temp == 2)
	{
		X = 350;
		Y = 350;
		Temp++;
	}
	else if (Temp == 3)
	{
		X = 330;
		Y = 330;
		Temp++;
	}*/

	Sector.X = X / dfSECTOR_GRID_X;
	Sector.Y = Y / dfSECTOR_GRID_Y;
	HP = DEFAULT_HP;

	// 캐릭터 추가
	gSector[Sector.Y][Sector.X].push_back(this);
	gCharacterMap.insert({ SessionID, this});
}

Character::~Character()
{
	gSector[Sector.Y][Sector.X].remove(this);
	gCharacterMap.erase(SessionID);
}

void Character::OnDamage(char Damage)
{
	HP -= Damage;
}

bool Character::IsDead()
{
	if (HP > 0)
		return false;

	return true;
}

Character* FindCharacter(unsigned int SessionID)
{
	return gCharacterMap[SessionID];
}

SectorPos FindSectorPos(unsigned int SessionID)
{
	Character* character = FindCharacter(SessionID);
	return character->Sector;
}