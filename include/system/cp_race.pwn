#if defined _SYSTEM_RACE_CP
	#endinput
#endif
#define _SYSTEM_RACE_CP

// ------------------------------------
#define RCP_ACTION_TYPE_NONE 	-1

// ------------------------------------
#define GetPlayerRaceCPInfo(%0,%1) 			g_player_rcp[%0][%1]
#define SetPlayerRaceCPInfo(%0,%1,%2) 		g_player_rcp[%0][%1] = %2

// ------------------------------------
enum E_PLAYER_RACE_CP_STRUCT
{
	RCP_TYPE,
	Float: RCP_POS_X,
	Float: RCP_POS_Y,
	Float: RCP_POS_Z,
	Float: RCP_NEXT_X,
	Float: RCP_NEXT_Y,
	Float: RCP_NEXT_Z,
	Float: RCP_SIZE,
	bool: RCP_ENABLED,
	RCP_ACTION_TYPE
};

// ------------------------------------
new g_player_rcp[MAX_PLAYERS][E_PLAYER_RACE_CP_STRUCT];
new const 
	g_rcp_default_values[E_PLAYER_RACE_CP_STRUCT] = 
{
	0,
	0.0,
	0.0,
	0.0,
	0.0,
	0.0,
	0.0,
	0.0,
	CP_STATUS_OFF,
	RCP_ACTION_TYPE_NONE
};

// ------------------------------------
stock ClearPlayerRCPInfo(playerid)
{
	g_player_rcp[playerid] = g_rcp_default_values;
}

// ------------------------------------
stock n_SetPlayerRaceCheckpoint(playerid, type, Float:x, Float:y, Float:z, Float:nextx, Float:nexty, Float:nextz, Float:size, action_type=RCP_ACTION_TYPE_NONE)
{
	SetPlayerRaceCPInfo(playerid, RCP_TYPE, type);
	
	SetPlayerRaceCPInfo(playerid, RCP_POS_X, x);
	SetPlayerRaceCPInfo(playerid, RCP_POS_Y, y);
	SetPlayerRaceCPInfo(playerid, RCP_POS_Z, z);
	
	SetPlayerRaceCPInfo(playerid, RCP_NEXT_X, nextx);
	SetPlayerRaceCPInfo(playerid, RCP_NEXT_Y, nexty);
	SetPlayerRaceCPInfo(playerid, RCP_NEXT_Z, nextz);
	SetPlayerRaceCPInfo(playerid, RCP_SIZE, size);
	
	SetPlayerRaceCPInfo(playerid, RCP_ACTION_TYPE, action_type);
	SetPlayerRaceCPInfo(playerid, RCP_ENABLED, true);
	
	return SetPlayerRaceCheckpoint(playerid, type, x, y, z, nextx, nexty, nextz, size);
}
#if defined _ALS_SetPlayerRaceCheckpoint
    #undef SetPlayerRaceCheckpoint
#else
    #define _ALS_SetPlayerCheckpoint
#endif
#define SetPlayerRaceCheckpoint n_SetPlayerRaceCheckpoint

stock n_IsPlayerInRaceCheckpoint(playerid)
{
	if(GetPlayerRaceCPInfo(playerid, RCP_ENABLED) == CP_STATUS_ON)
	{
		if(IsPlayerInRangeOfPoint(playerid, GetPlayerRaceCPInfo(playerid, RCP_SIZE), GetPlayerRaceCPInfo(playerid, RCP_POS_X), GetPlayerRaceCPInfo(playerid, RCP_POS_Y), GetPlayerRaceCPInfo(playerid, RCP_POS_Z)))
		{
			return 1;
		}
	}
	return 0;
}
#if defined _ALS_IsPlayerInRaceCheckpoint
    #undef IsPlayerInRaceCheckpoint
#else
    #define _ALS_IsPlayerInRaceCheckpoint
#endif
#define IsPlayerInRaceCheckpoint n_IsPlayerInRaceCheckpoint

stock n_DisablePlayerRaceCheckpoint(playerid)
{
	if(GetPlayerRaceCPInfo(playerid, RCP_ENABLED) == CP_STATUS_ON)
	{
		SetPlayerRaceCPInfo(playerid, RCP_ENABLED, CP_STATUS_OFF);
		DisablePlayerRaceCheckpoint(playerid);
		
		return 1;
	}
	return 0;
}
#if defined _ALS_DisablePlayerRaceCheckpoin
    #undef DisablePlayerRaceCheckpoint
#else
    #define _ALS_DisablePlayerRaceCheckpoin
#endif
#define DisablePlayerRaceCheckpoint n_DisablePlayerRaceCheckpoint