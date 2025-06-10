/*

	About: Convert Russian text to pawn include v1.2
	Author: Noname

*/

#if !defined _samp_included
	#error "Please include a_samp or a_npc before m_crp"
#endif

#if defined _m_crp_included_
	#endinput
#endif
#define _m_crp_included_

/*
	Define const
*/

#if !defined FIX_const
	#define FIX_const 0
	#define M_CRUSTOPWN_FIX_CLEAR
#endif

#if !FIX_const
	native Text:MCRP_TextDrawCreate(Float:x, Float:y, text[]) = TextDrawCreate;

	#if defined _ALS_TextDrawCreate
		#undef TextDrawCreate
	#else
		#define _ALS_TextDrawCreate
	#endif

	#define TextDrawCreate( MCRP_TextDrawCreate(

	native MCRP_TextDrawSetString(Text:text, string[]) = TextDrawSetString;

	#if defined _ALS_TextDrawSetString
		#undef TextDrawSetString
	#else
		#define _ALS_TextDrawSetString
	#endif

	#define TextDrawSetString( MCRP_TextDrawSetString(

	native PlayerText:MCRP_CreatePlayerTextDraw(playerid, Float:x, Float:y, const text[]) = CreatePlayerTextDraw;

	#if defined _ALS_CreatePlayerTextDraw
		#undef CreatePlayerTextDraw
	#else
		#define _ALS_CreatePlayerTextDraw
	#endif

	#define CreatePlayerTextDraw( MCRP_CreatePlayerTextDraw(

	native MCRP_PlayerTextDrawSetString(playerid, PlayerText:text, const string[]) = PlayerTextDrawSetString;

	#if defined _ALS_PlayerTextDrawSetString
		#undef PlayerTextDrawSetString
	#else
		#define _ALS_PlayerTextDrawSetString
	#endif

	#define PlayerTextDrawSetString( MCRP_PlayerTextDrawSetString(

	#if defined M_CRUSTOPWN_FIX_CLEAR
		#undef M_CRUSTOPWN_FIX_CLEAR
		#undef FIX_const
	#endif
#endif

/*
	Vars
*/

static const
	crp_server_text_aya[] = {"aó¢ôöeõüúùkûØÆo£pc¶yÅxâ§•°ß®©™´¨"}, // Ù, ˆ
	crp_server_text_AYA[] = {"AÄãÇÉEÑàÖÜKáMHOåPCèYÅXâçéäêëíìîï"};

/*
	Private functions
*/

static stock ConvertRusToPwn(const string[], buffer[])
{
	for (new c, i; (c = string[i]) != '\0'; i++) {
		switch (c) {
			case '‡'..'ˇ':
				buffer[i] = crp_server_text_aya[c - '‡'];
			case '¿'..'ﬂ':
				buffer[i] = crp_server_text_AYA[c - '¿'];
			case '∏':
				buffer[i] = 'e';
			case '®':
				buffer[i] = 'E';
			default:
				buffer[i] = c;
		}
	}
}

/*
	GameTextForAll
*/

stock CRusToPwn_GameTextForAll(const string[], time, style)
{
	new
		buffer[256 + 1];

	ConvertRusToPwn(string, buffer);
	return GameTextForAll(buffer, time, style);
}
#if defined _ALS_GameTextForAll
	#undef GameTextForAll
#else
	#define _ALS_GameTextForAll
#endif

#define GameTextForAll CRusToPwn_GameTextForAll

/*
	GameTextForPlayer
*/

stock CRusToPwn_GameTextForPlayer(playerid, const string[], time, style)
{
	new
		buffer[256 + 1];

	ConvertRusToPwn(string, buffer);
	return GameTextForPlayer(playerid, buffer, time, style);
}
#if defined _ALS_GameTextForPlayer
	#undef GameTextForPlayer
#else
	#define _ALS_GameTextForPlayer
#endif

#define GameTextForPlayer CRusToPwn_GameTextForPlayer

/*
	TextDrawCreate
*/

stock Text:CRusToPwn_TextDrawCreate(Float:x, Float:y, const text[])
{
	new
		buffer[256 + 1];

	ConvertRusToPwn(text, buffer);
	return TextDrawCreate(x, y, buffer);
}
#if defined _ALS_TextDrawCreate
	#undef TextDrawCreate
#else
	#define _ALS_TextDrawCreate
#endif

#define TextDrawCreate CRusToPwn_TextDrawCreate

/*
	TextDrawSetString
*/

stock CRusToPwn_TextDrawSetString(Text:text, const string[])
{
	new
		buffer[256 + 1];

	ConvertRusToPwn(string, buffer);
	return TextDrawSetString(text, buffer);
}
#if defined _ALS_TextDrawSetString
	#undef TextDrawSetString
#else
	#define _ALS_TextDrawSetString
#endif

#define TextDrawSetString CRusToPwn_TextDrawSetString

/*
	CreatePlayerTextDraw
*/

stock PlayerText:CRusToPwn_CreatePlayerTextDraw(playerid, Float:x, Float:y, const text[])
{
	new
		buffer[256 + 1];

	ConvertRusToPwn(text, buffer);
	return CreatePlayerTextDraw(playerid, x, y, buffer);
}
#if defined _ALS_CreatePlayerTextDraw
	#undef CreatePlayerTextDraw
#else
	#define _ALS_CreatePlayerTextDraw
#endif

#define CreatePlayerTextDraw CRusToPwn_CreatePlayerTextDraw

/*
	PlayerTextDrawSetString
*/

stock CRusToPwn_PlayerTextDrawSetStr(playerid, PlayerText:text, const string[])
{
	new
		buffer[256 + 1];

	ConvertRusToPwn(string, buffer);
	return PlayerTextDrawSetString(playerid, text, buffer);
}
#if defined _ALS_PlayerTextDrawSetString
	#undef PlayerTextDrawSetString
#else
	#define _ALS_PlayerTextDrawSetString
#endif

#define PlayerTextDrawSetString CRusToPwn_PlayerTextDrawSetStr