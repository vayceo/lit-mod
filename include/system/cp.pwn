#if defined _SYSTEM_CP
	#endinput
#endif
#define _SYSTEM_CP

// ------------------------------------
#define CP_STATUS_ON 	true
#define CP_STATUS_OFF 	false

// ------------------------------------
#define CP_ACTION_TYPE_NONE 	-1

// ------------------------------------
#define GetPlayerCPInfo(%0,%1) 		g_player_cp[%0][%1]
#define SetPlayerCPInfo(%0,%1,%2) 	g_player_cp[%0][%1] = %2

// ------------------------------------
enum E_PLAYER_CP_STRUCT
{
	Float: CP_POS_X,
	Float: CP_POS_Y,
	Float: CP_POS_Z,
	Float: CP_SIZE,
	bool: CP_ENABLED,
	CP_ACTION_TYPE
};

// ------------------------------------
new g_player_cp[MAX_PLAYERS][E_PLAYER_CP_STRUCT];
new const 
	g_cp_default_values[E_PLAYER_CP_STRUCT] = 
{
	0.0,
	0.0,
	0.0,
	0.0,
	CP_STATUS_OFF,
	CP_ACTION_TYPE_NONE
};

// ------------------------------------
stock ClearPlayerCPInfo(playerid)
{
	g_player_cp[playerid] = g_cp_default_values;
}

// ------------------------------------
stock n_SetPlayerCheckpoint(playerid, Float: x, Float: y, Float: z, Float: size, action_type=CP_ACTION_TYPE_NONE)
{
	SetPlayerCPInfo(playerid, CP_POS_X, x);
	SetPlayerCPInfo(playerid, CP_POS_Y, y);
	SetPlayerCPInfo(playerid, CP_POS_Z, z);
	SetPlayerCPInfo(playerid, CP_SIZE, size);
	
	SetPlayerCPInfo(playerid, CP_ACTION_TYPE, action_type);
	SetPlayerCPInfo(playerid, CP_ENABLED, true);
	
	return SetPlayerCheckpoint(playerid, x, y, z, size);
}
#if defined _ALS_SetPlayerCheckpoint
    #undef SetPlayerCheckpoint
#else
    #define _ALS_SetPlayerCheckpoint
#endif
#define SetPlayerCheckpoint n_SetPlayerCheckpoint

stock n_IsPlayerInCheckpoint(playerid, Float: size=1.0)
{
	if(GetPlayerCPInfo(playerid, CP_ENABLED) == CP_STATUS_ON)
	{
		if(IsPlayerInRangeOfPoint(playerid, GetPlayerCPInfo(playerid, CP_SIZE) + size, GetPlayerCPInfo(playerid, CP_POS_X), GetPlayerCPInfo(playerid, CP_POS_Y), GetPlayerCPInfo(playerid, CP_POS_Z)))
		{
			return 1;
		}
	}
	return 0;
}
#if defined _ALS_IsPlayerInCheckpoint
    #undef IsPlayerInCheckpoint
#else
    #define _ALS_IsPlayerInCheckpoint
#endif
#define IsPlayerInCheckpoint n_IsPlayerInCheckpoint

stock n_DisablePlayerCheckpoint(playerid)
{
	if(GetPlayerCPInfo(playerid, CP_ENABLED) == CP_STATUS_ON)
	{
		SetPlayerCPInfo(playerid, CP_ENABLED, CP_STATUS_OFF);
		DisablePlayerCheckpoint(playerid);
		
		return 1;
	}
	return 0;
}
#if defined _ALS_DisablePlayerCheckpoint
    #undef DisablePlayerCheckpoint
#else
    #define _ALS_DisablePlayerCheckpoint
#endif
#define DisablePlayerCheckpoint n_DisablePlayerCheckpoint