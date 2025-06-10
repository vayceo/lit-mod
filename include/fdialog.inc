#if defined _fdialog_included
    #endinput
#endif
#define _fdialog_included

#if !defined isnull
    #define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#define IsDialogOpen(%0,%1) 	(fg_playerDialogID[%0] == %1)
#define IsAnyDialogOpen(%0) 	(fg_playerDialogID[%0] != -1)
#define DLG(%0,%1,%2,%3,%4) 	forward dia_%0(%1,%2,%3,%4); public dia_%0(%1,%2,%3,%4)

static dfstring[12];
new fg_playerDialogID[MAX_PLAYERS];
new fg_playerDialogStyle[MAX_PLAYERS];

stock fg_ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[])
{
	if(!IsPlayerConnected(playerid)) return 0;
	fg_playerDialogID[playerid] = dialogid;
	fg_playerDialogStyle[playerid] = style;
	return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
}
#if defined _ALS_ShowPlayerDialog
    #undef ShowPlayerDialog
#else
    #define _ALS_ShowPlayerDialog
#endif
#define ShowPlayerDialog fg_ShowPlayerDialog
	
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) 
{
	if(listitem < 0) listitem = 0;
	if(fg_playerDialogStyle[playerid] == DIALOG_STYLE_INPUT || fg_playerDialogStyle[playerid] == DIALOG_STYLE_PASSWORD)
	{
		for(new id = (strlen(inputtext) - 1); id >= 0; id--) switch(inputtext[id]) { case '%', '{', '~', ''': inputtext[id] = '-'; }
	}
	#if defined OnDialogReceived
		if(!OnDialogReceived(playerid, dialogid, response, listitem, inputtext)) return 1;
	#endif
	if(fg_playerDialogID[playerid] != -1)
	{
	    format(dfstring, sizeof(dfstring), "dia_%i", fg_playerDialogID[playerid]);
 		fg_playerDialogID[playerid] = -1;
		CallLocalFunction(dfstring, "iiis", playerid, response, listitem, isnull(inputtext) ? ("\1") : inputtext);
	}
	#if defined fg_OnDialogResponse
		return fg_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
	    return 1;
	#endif
}
#if defined _ALS_OnDialogResponse
    #undef OnDialogResponse
#else
    #define _ALS_OnDialogResponse
#endif
#if defined fg_OnDialogResponse
	forward fg_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif
#define	OnDialogResponse fg_OnDialogResponse
#if defined OnDialogReceived
	forward OnDialogReceived(playerid, dialogid, response, listitem, inputtext[]);
#endif

public OnPlayerConnect(playerid)
{
    fg_playerDialogID[playerid] = -1;
    #if defined fg_OnPlayerConnect
		return fg_OnPlayerConnect(playerid);
	#else
	    return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#if defined fg_OnPlayerConnect
	forward fg_OnPlayerConnect(playerid);
#endif
#define OnPlayerConnect fg_OnPlayerConnect
