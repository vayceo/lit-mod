/*

	About: Dialog Processor include v3.2
	Author: Noname

*/

#if !defined _samp_included
	#error "Please include a_samp or a_npc before m_dialog"
#endif

#if defined _m_dialog_included_
	#endinput
#endif
#define _m_dialog_included_

/*
	Define const
*/

#if !defined PROCESSOR_DIALOG_ID
	#define PROCESSOR_DIALOG_ID 32767
#endif

#if !defined MAX_FUNCTION_NAME
	#define MAX_FUNCTION_NAME 32
#endif

#if !defined M_DIALOG_DialogForPlayer
	#define M_DIALOG_DialogForPlayer 0
#else
	#undef M_DIALOG_DialogForPlayer
	#define M_DIALOG_DialogForPlayer 1
#endif

#if !defined FIX_const
	#define FIX_const 0
	#define M_DIALOG_FIX_CLEAR
#endif

#if !FIX_const
	native MD_ShowPlayerDialog(playerid, dialogid, style, const caption[], const info[], const button1[], const button2[]) = ShowPlayerDialog;

	#if defined _ALS_ShowPlayerDialog
		#undef ShowPlayerDialog
	#else
		#define _ALS_ShowPlayerDialog
	#endif

	#define ShowPlayerDialog( MD_ShowPlayerDialog(

	#if defined M_DIALOG_FIX_CLEAR
		#undef M_DIALOG_FIX_CLEAR
		#undef FIX_const
	#endif
#endif

/*
	Define functions
*/

#define Dialog_Create:%0(%1) \
	forward DC_%0(%1); \
	public DC_%0(%1)

#define Dialog_Show::%0(%1) \
	DC_%0(%1)

#define Dialog_Response:%0(%1) \
	forward DR_%0(%1); \
	public DR_%0(%1)

#define Dialog: #

#if !defined isnull
    #define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

/*
	Vars
*/

static
	bool:d_player_open[MAX_PLAYERS char],
	d_player_function[MAX_PLAYERS][MAX_FUNCTION_NAME + 1 char];

#if M_DIALOG_DialogForPlayer
static
	d_player_dialog_id[MAX_PLAYERS];
#endif

/*
	Dialog_Open
*/

#if defined _nex_ac_included
stock Dialog_Open(playerid, const function[], style, caption[], info[], button1[], button2[])
#else
stock Dialog_Open(playerid, const function[], style, const caption[], const info[], const button1[], const button2[])
#endif
{
	d_player_open{playerid} = true;
	d_player_function[playerid] = !"DR_";
	strcat(d_player_function[playerid], function);

#if M_DIALOG_DialogForPlayer

	new
		idx = funcidx(d_player_function[playerid]);

	d_player_dialog_id[playerid] = ((idx != -1) ? (idx) : (0));
	return ShowPlayerDialog(playerid, d_player_dialog_id[playerid], style, caption, info, button1, button2);
#else
	return ShowPlayerDialog(playerid, PROCESSOR_DIALOG_ID, style, caption, info, button1, button2);
#endif
}

/*
	Dialog_IsOpen
*/

stock Dialog_IsOpen(playerid)
{
	return _:d_player_open{playerid};
}

/*
	Dialog_Close
*/

stock Dialog_Close(playerid, bool:showDialog = true)
{
	d_player_open{playerid} = false;

	if (showDialog == true)
		return ShowPlayerDialog(playerid, -1, DIALOG_STYLE_MSGBOX, !" ", !" ", !" ", !"");

	return 1;
}

/*
	OnDialogResponse
*/

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
#if M_DIALOG_DialogForPlayer
	if (dialogid == d_player_dialog_id[playerid]) {
#else
	if (dialogid == PROCESSOR_DIALOG_ID) {
#endif
		if (Dialog_IsOpen(playerid)) {
			if (isnull(inputtext)) {
				Dialog_Close(playerid, false);

				if (funcidx(d_player_function[playerid]) != -1)
					CallLocalFunction(d_player_function[playerid], !"iiis", playerid, response, listitem, !"\1");
				return 1;
			}
			else {
				for (new i; i < inputtext[i]; i++) {
					if (inputtext[i] == '%')
						inputtext[i] = '#';
					else if (inputtext[i] == '{' && inputtext[i + 7] == '}')
						strdel(inputtext, i, i + 8);
				}
				Dialog_Close(playerid, false);

				if (funcidx(d_player_function[playerid]) != -1)
					CallLocalFunction(d_player_function[playerid], !"iiis", playerid, response, listitem, inputtext);
				return 1;
			}
		}
		return 0;
	}

	#if defined m_dialog_OnDialogResponse
		return m_dialog_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else
		return 0;
	#endif
}

#if defined _ALS_OnDialogResponse
	#undef OnDialogResponse
#else
	#define _ALS_OnDialogResponse
#endif
#define OnDialogResponse m_dialog_OnDialogResponse
#if defined m_dialog_OnDialogResponse
	forward m_dialog_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif