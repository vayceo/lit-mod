#if defined _weapon_included
	#endinput
#endif

#define _weapon_included
#pragma library samp
#include <a_samp>

#define MAX_WEAPON_SLOTS	(13)

#define SetPlayerWeaponInfo(%0,%1,%2,%3)		g_player_weapon[%0][%1][%2] = %3
#define GetPlayerWeaponInfo(%0,%1,%2)			g_player_weapon[%0][%1][%2]
#define AddPlayerWeaponInfo(%0,%1,%2,%3,%4)		g_player_weapon[%0][%1][%2] %3= %4

enum E_PLAYER_WEAPON_STRUCT
{
	W_ID,
	W_AMMO
}

new g_player_weapon[MAX_PLAYERS][MAX_WEAPON_SLOTS][E_PLAYER_WEAPON_STRUCT];

new g_player_reloading[MAX_PLAYERS][2]; // защита от стрельбы без перезарядки

stock GetWeaponSlot(weapon_id)
{
	new slot;

	switch(weapon_id)
	{
		case 0, 1:      	slot = 0;
		case 2..9:      	slot = 1;
		case 22..24:    	slot = 2;
		case 25..27:    	slot = 3;
		case 28, 29, 32:  	slot = 4;
		case 30, 31:     	slot = 5;
		case 33, 34:     	slot = 6;
		case 35..38:    	slot = 7;
		case 16..18:    	slot = 8;
		case 41..43:    	slot = 9;
		case 10..15:    	slot = 10;
		case 44..46:    	slot = 11;
		case 40:        	slot = 12;
	}

	return slot;
}

stock n_GivePlayerWeapon(playerid, weapon_id, weapon_ammo)
{
	new weapon_slot = GetWeaponSlot(weapon_id);

	SetPlayerWeaponInfo(playerid, weapon_slot, W_ID,		weapon_id);
	AddPlayerWeaponInfo(playerid, weapon_slot, W_AMMO, +, 	weapon_ammo);

	GivePlayerWeapon(playerid, weapon_id, weapon_ammo);
}

stock n_TakePlayerWeapon(playerid, weapon_id)
{
	new weapon_slot = GetWeaponSlot(weapon_id),
		slot_weapon,
		slot_ammo;

	for(new idx; idx < MAX_WEAPON_SLOTS; idx ++)
	{
		GetPlayerWeaponData(playerid, idx, slot_weapon, slot_ammo);

		if(idx == weapon_slot && weapon_id == slot_weapon)
		{
			n_GivePlayerWeapon(playerid, weapon_id, -slot_ammo);

			break;
		}
	}
}

stock n_ResetPlayerWeapons(playerid)
{
	for(new idx; idx < MAX_WEAPON_SLOTS; idx ++)
	{
		SetPlayerWeaponInfo(playerid, idx, W_ID, 	0);
		SetPlayerWeaponInfo(playerid, idx, W_AMMO,	0);
	}

	ResetPlayerWeapons(playerid);
}

#if defined _ALS_GivePlayerWeapon
	#undef GivePlayerWeapon
#else
	#define _ALS_GivePlayerWeapon
#endif
#define GivePlayerWeapon n_GivePlayerWeapon

#if defined _ALS_ResetPlayerWeapons
	#undef ResetPlayerWeapons
#else
	#define _ALS_ResetPlayerWeapons
#endif
#define ResetPlayerWeapons n_ResetPlayerWeapons