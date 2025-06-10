#if defined _SYSTEM_PICKUP
	#endinput
#endif
#define _SYSTEM_PICKUP

// ------------------------------------
#define GetPickupInfo(%0,%1)		g_pickup_info[%0][%1]
#define SetPickupInfo(%0,%1,%2)		g_pickup_info[%0][%1] = %2
#define ClearPickupInfo(%0)			g_pickup_info[%0] = g_pickup_default_values
#define IsPickupExists(%0)			g_pickup_info[%0][P_CREATED]
#define IsValidPickupID(%0)			(0 <= %0 < MAX_PICKUPS)

// ------------------------------------
#define PICKUP_ACTION_TYPE_NONE -1
#define PICKUP_ACTION_ID_NONE 	-1

// ------------------------------------
forward OnPlayerPickUpPickupEx(playerid, pickupid, action_type, action_id);

// ------------------------------------
enum E_PICKUP_STRUCT
{
	P_MODEL,
	P_TYPE, 
	Float: P_POS_X,
	Float: P_POS_Y,
	Float: P_POS_Z,
	P_VIRTUAL_WORLD,
	// -------------
	P_ACTION_TYPE,
	P_ACTION_ID,
	// -------------
	bool: P_CREATED,
	// -------------
	P_DYNAMIC_ZONE
};
new g_pickup_info[MAX_PICKUPS][E_PICKUP_STRUCT];
new 
	g_pickup_default_values[E_PICKUP_STRUCT] = 
{
	0,
	0,
	0.0,
	0.0,
	0.0,
	0,
	PICKUP_ACTION_TYPE_NONE,
	PICKUP_ACTION_ID_NONE,
	false,
	-1
};
new g_pickup_flood[MAX_PLAYERS] = {0, ...};

stock n_CreatePickup(model, type, Float:X, Float:Y, Float:Z, Virtualworld, action_type = PICKUP_ACTION_TYPE_NONE, action_id = PICKUP_ACTION_ID_NONE)
{
	
	static n_pickupid = -1;
	n_pickupid = CreatePickup(model, type, X, Y, Z, Virtualworld);
	
	if(n_pickupid != -1)
	{
		SetPickupInfo(n_pickupid, P_MODEL, 	model);
		SetPickupInfo(n_pickupid, P_TYPE, 	type);
		
		SetPickupInfo(n_pickupid, P_POS_X, 	X);
		SetPickupInfo(n_pickupid, P_POS_Y, 	Y);
		SetPickupInfo(n_pickupid, P_POS_Z, 	Z);
		
		SetPickupInfo(n_pickupid, P_VIRTUAL_WORLD, Virtualworld);
		
		SetPickupInfo(n_pickupid, P_ACTION_TYPE, 	action_type);
		SetPickupInfo(n_pickupid, P_ACTION_ID, 		action_id);
		
		SetPickupInfo(n_pickupid, P_CREATED, true);

		SetPickupInfo(n_pickupid, P_DYNAMIC_ZONE, CreateDynamicSphere(X, Y, Z, 1.4, Virtualworld));
	}
	
	return n_pickupid; // The ID of the created pickup, -1 on failure (pickup max limit).
}
#if defined _ALS_CreatePickup
    #undef CreatePickup
#else
    #define _ALS_CreatePickup
#endif
#define CreatePickup n_CreatePickup

stock n_DestroyPickup(pickupid)
{
	if(IsPickupExists(pickupid))
	{
		ClearPickupInfo(pickupid);

		DestroyDynamicArea(GetPickupInfo(pickupid, P_DYNAMIC_ZONE));
	}
	return DestroyPickup(pickupid); // This function does not return any specific values;
}
#if defined _ALS_DestroyPickup
    #undef DestroyPickup
#else
    #define _ALS_DestroyPickup
#endif
#define DestroyPickup n_DestroyPickup

public OnPlayerPickUpPickup(playerid, pickupid)
{
	if(g_pickup_flood[playerid] <= GetTickCount())
	{
		g_pickup_flood[playerid] = GetTickCount() + 250;

		new 
			action_type = PICKUP_ACTION_TYPE_NONE, 
			action_id = PICKUP_ACTION_ID_NONE;
		
		if(IsValidPickupID(pickupid))
		{
			action_type = GetPickupInfo(pickupid, P_ACTION_TYPE);
			action_id = GetPickupInfo(pickupid, P_ACTION_ID);
		}
		return OnPlayerPickUpPickupEx(playerid, pickupid, action_type, action_id);
	}
	return 0;
}

public OnGameModeInit()
{
    for(new idx = 0; idx < MAX_PICKUPS; idx ++)
	{
		ClearPickupInfo(idx);
	}
	
#if defined n_OnGameModeInit
    n_OnGameModeInit();
#endif
    return 1;
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit n_OnGameModeInit
#if defined n_OnGameModeInit
forward n_OnGameModeInit();
#endif  