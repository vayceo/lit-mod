#include <YSI_Coding\y_hooks>

// ............. [ DEFINES ] .............
#define SPD ShowPlayerDialog
#define SCM SendClientMessage
#define DSL DIALOG_STYLE_LIST
#define SC "{ffff00}| {ffffff}"
#define USC "{ff2400}| {ffffff}"
// ............. [ COLORS ] .............
#define color_white 0xFFFFFF
#define         color_gray              0x999999
// ............. [ NEWS ] .............
// ............. [ DIALOGS ] .............
DIALOG_TUNE(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:TUNE, DSL, 
        "{3FD7D0}LIT MOBILE {FFFFFF}| ТЮНИНГ",
        "{FFFFFF}| Сменить цвет\n\
		Компоненты",
        "Далее", "Отмена"
    );
    return 1;
}

DIALOG_COLOR(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:COLOR, DSL, 
        "LIT MOBILE | Выберите цвет", 
        "Белый\n\
        Черный\n\
        Красный\n\
        Желтый\n\
        Синий",
        "Выбрать", "Закрыть"
    );
    return 1;
}

DIALOG_COMP(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:COMP, DSL, 
        "LIT MOBILE | Выберите компонент",
        "Гидравлика\n\
        Нитро",
        "Выбрать", "Закрыть"
    );
    return 1;
}
// ............. [ COMMANDS ] .............
CMD:tune(playerid)
{
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
	    DIALOG_TUNE(playerid);
	}
	else return SCM(playerid, color_gray, ""USC"Вы должны быть за рулем.");
	return 1;
}

// ............. [ RESPONSES ] .............
Dialog_Response:TUNE(playerid, response, listitem)
{
    if (!response) {
        return 1;
    }

    switch (listitem) {
        case 0: DIALOG_COLOR(playerid);
        case 1: DIALOG_COMP(playerid);
    }
    return 1;
}

Dialog_Response:COLOR(playerid, response, listitem)
{
    if (!response) {
        return 1;
    }

    new vehicleid = GetPlayerVehicleID(playerid);
    switch (listitem) {
        case 0: ChangeVehicleColor(vehicleid, 1, 0); // Белый
        case 1: ChangeVehicleColor(vehicleid, 0, 0); // Черный
        case 2: ChangeVehicleColor(vehicleid, 3, 0); // Красный
        case 3: ChangeVehicleColor(vehicleid, 6, 0); // Желтый
        case 4: ChangeVehicleColor(vehicleid, 2, 0); // Синий
    }
    return 1;
}

Dialog_Response:COMP(playerid, response, listitem)
{
    if (!response) {
        return 1;
    }

    new vehicleid = GetPlayerVehicleID(playerid);
    switch (listitem) {
        case 0: AddVehicleComponent(vehicleid, 1087); // Гидравлика
        case 1: AddVehicleComponent(vehicleid, 1010); // Нитро
    }
    return 1;
}

// ............. [ STOCKS ] .............
// ............. [ HOOKS ] .............