/*

================================================================================
							KickBanFix.inc
							  By fall3n


native Kick(playerid, delay_ms=150); //If used as Kick(playerid); delay_ms will be set as 150 (default value)
native Ban(playerid, delay_ms=150);
native BanEx(playerid, const reason[], delay_ms=150);
native IsKickBanProcessed(playerid); //Returns : 1 if kick/ban is being processed, 0 if not.

"delay_ms" is an optional parameter. It stands for the time(in milli-seconds) to
be delayed for processing kick/ban/banex functions. By default it's 150 ms.

This include also ensures that player's data won't be received by the server if
they're kicked/banned from the server.

GitHub release link:
https://github.com/falle3n/KickBanFix


================================================================================            */

#tryinclude <a_samp>


static

	f3_KBRProcessed[MAX_PLAYERS],
	f3_KBRBanExRes[MAX_PLAYERS][128],
	f3_KBRTimer[MAX_PLAYERS];



static stock f3strcpy(dest[], const source[], size = sizeof(dest))
{
	return strcat((dest[0] = '\0', dest), source, size);
}


stock IsKickBanProcessed(playerid)
{
	if(f3_KBRProcessed[playerid] >= 1) return 1;
	return 0;
}



stock f3_Kick(playerid, delay_ms = 150)
{
	if(!IsPlayerConnected(playerid) || f3_KBRProcessed[playerid]) return 0;

	f3_KBRProcessed[playerid] = 1;
	f3_KBRTimer[playerid] = SetTimerEx("f3KickBanFix", delay_ms, false, "d", playerid);

	return 1;
}

stock f3_Ban(playerid, delay_ms = 150)
{
	if(!IsPlayerConnected(playerid) || f3_KBRProcessed[playerid]) return 0;

	f3_KBRProcessed[playerid] = 2;
	f3_KBRTimer[playerid] = SetTimerEx("f3KickBanFix", delay_ms, false, "d", playerid);

	return 1;
}

stock f3_BanEx(playerid, const reason[], delay_ms = 150)
{
	if(!IsPlayerConnected(playerid) || f3_KBRProcessed[playerid]) return 0;

	f3strcpy(f3_KBRBanExRes[playerid], reason, 128);
	f3_KBRProcessed[playerid] = 3;
	f3_KBRTimer[playerid] = SetTimerEx("f3KickBanFix", delay_ms, false, "d", playerid);

	return 1;
}

forward f3KickBanFix(playerid);

public f3KickBanFix(playerid)
{
	if(f3_KBRTimer[playerid] == -1) return 0;
	switch(f3_KBRProcessed[playerid])
	{
	    case 1 :
	    {
	        f3_KBRProcessed[playerid] = 0;
	        f3_KBRTimer[playerid] = -1;

			return Kick(playerid);
		}
		case 2 :
		{
		    f3_KBRProcessed[playerid] = 0;
		    f3_KBRTimer[playerid] = -1;

		    return Ban(playerid);
		}
		case 3 :
		{
		    f3_KBRProcessed[playerid] = 0;
		    f3_KBRTimer[playerid] = -1;

		    return BanEx(playerid, f3_KBRBanExRes[playerid]);
		}
		default :
		{
			f3_KBRProcessed[playerid] = 0;
			f3_KBRTimer[playerid] = -1;
		}
	}
	return 1;
}

public OnPlayerConnect(playerid)
{
	f3_KBRProcessed[playerid] = 0;
	f3_KBRTimer[playerid] = -1;

	#if defined f3_KBROnPlayerConnect
	return f3_KBROnPlayerConnect(playerid);
	
	#else
	
	return 1;
	
	#endif
	
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect f3_KBROnPlayerConnect

#if defined f3_KBROnPlayerConnect
forward f3_KBROnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
	if(f3_KBRTimer[playerid] != -1)
	{
		f3KickBanFix(playerid);
	}
	#if defined f3_KBROnPlayerDisconnect
	return f3_KBROnPlayerDisconnect(playerid, reason);
	
	#else
	
	return 1;
	
	#endif
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect f3_KBROnPlayerDisconnect

#if defined f3_KBROnPlayerDisconnect
forward f3_KBROnPlayerDisconnect(playerid, reason);
#endif

public OnPlayerUpdate(playerid)
{
	if(f3_KBRProcessed[playerid]) return 0;
	#if defined f3_KBROnPlayerUpdate

	return f3_KBROnPlayerUpdate(playerid);

	#else

	return 1;

	#endif
}

#if defined _ALS_OnPlayerUpdate
	#undef OnPlayerUpdate
#else
	#define _ALS_OnPlayerUpdate
#endif

#define OnPlayerUpdate f3_KBROnPlayerUpdate

#if defined f3_KBROnPlayerUpdate
forward f3_KBROnPlayerUpdate(playerid);
#endif


public OnPlayerCommandText(playerid, cmdtext[])
{
	if(f3_KBRProcessed[playerid]) return 1;
	#if defined f3_KBROnPlayerCommandText

	return f3_KBROnPlayerCommandText(playerid, cmdtext);

	#else

	return 0;

	#endif
}

#if defined _ALS_OnPlayerCommandText
	#undef OnPlayerCommandText
#else
	#define _ALS_OnPlayerCommandText
#endif

#define OnPlayerCommandText f3_KBROnPlayerCommandText

#if defined f3_KBROnPlayerCommandText
forward f3_KBROnPlayerCommandText(playerid, cmdtext[]);
#endif



public OnPlayerText(playerid, text[])
{
	if(f3_KBRProcessed[playerid]) return 0;
	#if defined f3_KBROnPlayerText

	return f3_KBROnPlayerText(playerid, text);

	#else

	return 1;

	#endif
}

#if defined _ALS_OnPlayerText
	#undef OnPlayerText
#else
	#define _ALS_OnPlayerText
#endif

#define OnPlayerText f3_KBROnPlayerText

#if defined f3_KBROnPlayerText
forward f3_KBROnPlayerText(playerid, text[]);
#endif

#if defined OnPlayerWeaponShot //Checking if it's 0.3z

	public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
	{
		if(f3_KBRProcessed[playerid]) return 0;
		#if defined f3_KBROnPlayerTakeDamage

		return f3_KBROnPlayerTakeDamage(playerid, issuerid, amount, weaponid, bodypart);

		#else

		return 1;

		#endif
	}

	#if defined _ALS_OnPlayerTakeDamage
	    #undef OnPlayerTakeDamage
	#else
	    #define _ALS_OnPlayerTakeDamage
	#endif

	#define OnPlayerTakeDamage f3_KBROnPlayerTakeDamage

	#if defined f3_KBROnPlayerTakeDamage
	forward f3_KBROnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart);
	#endif




	public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
	{
	    if(f3_KBRProcessed[playerid]) return 0;
	    #if defined f3_KBROnPlayerWeaponShot

	    return f3_KBROnPlayerWeaponShot(playerid, weaponid, hittype, hitid, fX, fY, fZ);

	    #else

	    return 1;

	    #endif
	}

	#if defined _ALS_OnPlayerWeaponShot
	    #undef OnPlayerWeaponShot
	#else
	    #define _ALS_OnPlayerWeaponShot
	#endif

	#define OnPlayerWeaponShot f3_KBROnPlayerWeaponShot

	#if defined f3_KBROnPlayerWeaponShot
	forward f3_KBROnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ);
	#endif



	public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z,
	    Float:vel_x, Float:vel_y, Float:vel_z)
	{

	    if(f3_KBRProcessed[playerid]) return 0;
	    #if defined f3_KBROnUnoccupiedVehicleUpdate

		return f3_KBROnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z,
		    Float:vel_x, vel_y, vel_z);

		#else

		return 1;

		#endif

	}

	#if defined _ALS_OnUnoccupiedVehicleUpdate
	    #undef OnUnoccupiedVehicleUpdate
	#else
	    #define _ALS_OnUnoccupiedVehicleUpdate
	#endif

	#define OnUnoccupiedVehicleUpdate f3_KBROnUnoccupiedVehicleUpdate

	#if defined f3_KBROnUnoccupiedVehicleUpdate
	forward f3_KBROnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z,
	    Float:vel_x, Float:vel_y, Float:vel_z);
	#endif



#else

	public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid)
	{
	    if(f3_KBRProcessed[playerid]) return 0;
	    #if defined f3_KBROnPlayerTakeDamage

	    return f3_KBROnPlayerTakeDamage(playerid, issuerid, amount, weaponid);

	    #else

	    return 1;

	    #endif
 	}

	#if defined _ALS_OnPlayerTakeDamage
	    #undef OnPlayerTakeDamage
	#else
	    #define _ALS_OnPlayerTakeDamage
	#endif

	#define OnPlayerTakeDamage f3_KBROnPlayerTakeDamage

	#if defined f3_KBROnPlayerTakeDamage
	forward f3_KBROnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid);
	#endif


 	public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat)
 	{
 	    if(f3_KBRProcessed[playerid]) return 0;
 	    #if defined f3_KBROnUnoccupiedVehicleUpdate

 	    return f3_KBROnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat);

 	    #else

 	    return 1;

 	    #endif
	}

	#if defined _ALS_OnUnoccupiedVehicleUpdate
	    #undef OnUnoccupiedVehicleUpdate
	#else
	    #define _ALS_OnUnoccupiedVehicleUpdate
	#endif

	#define OnUnoccupiedVehicleUpdate f3_KBROnUnoccupiedVehicleUpdate

	#if defined f3_KBROnUnoccupiedVehicleUpdate
	forward f3_KBROnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat);
	#endif


#endif

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(f3_KBRProcessed[playerid]) return 1;
	#if defined f3_KBROnDialogResponse

	return f3_KBROnDialogResponse(playerid, dialogid, response, listitem, inputtext);

	#else

	return 0;

	#endif
}

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif

#define OnDialogResponse f3_KBROnDialogResponse

#if defined f3_KBROnDialogResponse
forward f3_KBROnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif



public OnPlayerDeath(playerid, killerid, reason)
{
	if(f3_KBRProcessed[playerid]) return 0;
	#if defined f3_KBROnPlayerDeath

	return f3_KBROnPlayerDeath(playerid, killerid, reason);

	#else

	return 1;

	#endif
}

#if defined _ALS_OnPlayerDeath
	#undef OnPlayerDeath
#else
	#define _ALS_OnPlayerDeath
#endif

#define OnPlayerDeath f3_KBROnPlayerDeath

#if defined f3_KBROnPlayerDeath
forward f3_KBROnPlayerDeath(playerid, killerid, reason);
#endif

public OnVehicleMod(playerid, vehicleid, componentid)
{
	if(f3_KBRProcessed[playerid]) return 0;
	#if defined f3_KBROnVehicleMod

	return f3_KBROnVehicleMod(playerid, vehicleid, componentid);

	#else

	return 1;

	#endif
}

#if defined _ALS_OnVehicleMod
	#undef OnVehicleMod
#else
	#define _ALS_OnVehicleMod
#endif

#define OnVehicleMod f3_KBROnVehicleMod

#if defined f3_KBROnVehicleMod
forward f3_KBROnVehicleMod(playerid, vehicleid, componentid);
#endif


public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	if(f3_KBRProcessed[playerid]) return 0;
	#if defined f3_KBROnVehicleRespray

	return f3_KBROnVehicleRespray(playerid, vehicleid, color1, color2);

	#else

	return 1;

	#endif
}

#if defined _ALS_OnVehicleRespray
	#undef OnVehicleRespray
#else
	#define _ALS_OnVehicleRespray
#endif

#define OnVehicleRespray f3_KBROnVehicleRespray

#if defined f3_KBROnVehicleRespray
forward f3_KBROnVehicleRespray(playerid, vehicleid, color1, color2);
#endif




#if defined _ALS_Kick
	#undef Kick
#else
	#define _ALS_Kick
#endif

#if defined _ALS_Ban
	#undef Ban
#else
	#define _ALS_Ban
#endif

#if defined _ALS_BanEx
	#undef BanEX
#else
	#define _ALS_BanEx
#endif

#define Kick 	f3_Kick
#define Ban     f3_Ban
#define BanEx   f3_BanEx


