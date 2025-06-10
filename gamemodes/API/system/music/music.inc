#define br   "{FF6347}"

CMD:music(playerid)
{
    Dialog_Show::LIST_MUSIC(playerid);
}

hook OnPlayerConnect(playerid)
{
    PlayAudioStreamForPlayer(playerid, "https://d.zaix.ru/f5d9.mp3");
    return Y_HOOKS_CONTINUE_RETURN_1;
}

CMD:musicoff(playerid)
{
    PlayerPlayStream(playerid, "");
}

Dialog_Create:LIST_MUSIC(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:LIST_MUSIC, DSL, 
        ""br""SERVER_NAME" {FFFFFFF}| LitSound",
        ""br"1. {FFFFFF}FORTUNA 812\n"\
        ""br"2. {FFFFFF}Литвин",
        "Выбрать", "Закрыть"
    );
    return 1;
}

Dialog_Create:MUSIC_FORTUNA(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:MUSIC_FORTUNA, DSL, 
        ""br""SERVER_NAME" {FFFFFFF}| FORTUNA 812",
        ""br"1. {FFFFFF}Paris Love\n"\
        ""br"2. {FFFFFF}Страхи\n"\
		""br"2. {FFFFFF}Ангел",
        "Выбрать", "Закрыть"
    );
    return 1;
}

Dialog_Response:LIST_MUSIC(playerid, response, listitem)
{
	if (!response) {
		return 1;
	}
	switch (listitem) {
		case 0: {
			Dialog_Show::MUSIC_FORTUNA(playerid);
		}
		case 1: {
				Dialog_Show::MUSIC_FORTUNA(playerid);
				return 1;
			}
		}
	return 1;
}

Dialog_Response:MUSIC_FORTUNA(playerid, response, listitem)
{
    if (!response) {
        return 1;
    }
    switch (listitem) {
        case 0: {
            PlayerPlayStream(playerid, "");
            SendClientMessage(playerid, color_red, "Вы включили музыку, для выключения введите команду /musicoff");
            PlayerPlayStream(playerid, "http://rwhack.space/sound/fortuna/paris.mp3");
        }
        case 1: {
            PlayerPlayStream(playerid, "");
            SendClientMessage(playerid, color_red, "Вы включили музыку, для выключения введите команду /musicoff");
            PlayerPlayStream(playerid, "http://rwhack.space/sound/fortuna/strahi.mp3");
            return 1;
        }
        case 2: {
            //PlayerPlayStream(playerid, "");
            SendClientMessage(playerid, color_red, "Вы включили музыку, для выключения введите команду /musicoff");
            PlayerPlayStream(playerid, "http://46.174.49.118/sound/fortuna/angel.mp3");
            return 1;
        }
    }
    return 1;
}

