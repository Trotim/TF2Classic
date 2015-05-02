//====== Copyright � 1996-2005, Valve Corporation, All rights reserved. =======//
//
// Purpose: Deathmatch weapon spawning entity.
//
//=============================================================================//
#include "cbase.h"
#include "tf_gamerules.h"
#include "tf_shareddefs.h"
#include "tf_player.h"
#include "tf_team.h"
#include "engine/IEngineSound.h"
#include "entity_weaponspawn.h"
#include "tf_weaponbase.h"
#include "basecombatcharacter.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

extern CTFWeaponInfo *GetTFWeaponInfo(int iWeapon);

#define TF_HEALTHKIT_PICKUP_SOUND	"HealthKit.Touch"

BEGIN_DATADESC(CWeaponSpawner)

	DEFINE_KEYFIELD(m_iWeaponNumber, FIELD_INTEGER, "WeaponNumber"),

END_DATADESC()

IMPLEMENT_SERVERCLASS_ST(CWeaponSpawner, DT_WeaponSpawner)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(tf_weaponspawner, CWeaponSpawner);

//-----------------------------------------------------------------------------
// Purpose: Spawn function 
//-----------------------------------------------------------------------------
void CWeaponSpawner::Spawn(void)
{
	pWeaponInfo = GetTFWeaponInfo(m_iWeaponNumber);
	Precache();

	SetModel(pWeaponInfo->szWorldModel);
	BaseClass::Spawn();
}

//-----------------------------------------------------------------------------
// Purpose: Precache function 
//-----------------------------------------------------------------------------
void CWeaponSpawner::Precache(void)
{
	PrecacheScriptSound(TF_HEALTHKIT_PICKUP_SOUND);
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
bool CWeaponSpawner::MyTouch(CBasePlayer *pPlayer)
{
	bool bSuccess = false;

	if (ValidTouch(pPlayer))
	{
		CTFPlayer *pTFPlayer = dynamic_cast<CTFPlayer*>(pPlayer);
		CTFWeaponBase *pWeapon = pTFPlayer->Weapon_GetWeaponByType(pWeaponInfo->m_iWeaponType);

		if (pWeapon)
		{
			if (pWeapon->GetWeaponID() == m_iWeaponNumber)
			{
				pPlayer->GiveAmmo(999, pWeaponInfo->iAmmoType);
			}
			else
			{
				pTFPlayer->Weapon_Detach(pWeapon);
				UTIL_Remove(pWeapon);
			}
		}

		if (pPlayer->GiveNamedItem(pWeaponInfo->szClassName))
		{
			CSingleUserRecipientFilter user(pPlayer);
			user.MakeReliable();

			UserMessageBegin(user, "ItemPickup");
			WRITE_STRING(GetClassname());
			MessageEnd();

			EmitSound(user, entindex(), TF_HEALTHKIT_PICKUP_SOUND);

			bSuccess = true;
		}
	}

	return bSuccess;
}