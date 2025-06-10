#include <YSI_Coding\y_hooks>

// ............. [ DEFINES ] .............
#define SPD ShowPlayerDialog
#define SCM SendClientMessage
#define DSL DIALOG_STYLE_LIST
#define SC "{ffff00}| {ffffff}"
#define USC "{ff2400}| {ffffff}"
// ............. [ COLORS ] .............
#define color_white 0xFFFFFF
// ............. [ NEWS ] .............
new playerVehicleID[MAX_PLAYERS];

// ............. [ DIALOGS ] .............
DIALOG_CAR(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:CAR_LIST, DSL, 
        "{3FD7D0}LIT MOBILE {FFFFFF}| АВТО", 
        "VAZ\n\
        Mercedes\n\
        BMW\n\
        Toyota\n\
        Lexus\n\
        Porsche\n\
        Китай\n\
        Мото\n\
        Полиция", 
        "Далее", "Отмена"
    );
    return 1;
}

DIALOG_VAZ(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:CAR_VAZ, DSL, 
        "VAZ", "2101\n\
        2105\n\
        2106\n\
        2109\n\
        2110\n\
        2112\n\
        2114\n\
        Granta\n\
        Priora", 
        "Далее", "Отмена"
    );
    return 1;
}

DIALOG_LEXUS(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:CAR_LEXUS, DSL, 
        "Lexus", "Lexus 570\n\
        ISF",
        "Далее", "Отмена"
    );
    return 1;
}

DIALOG_TOYOTA(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:CAR_TOYOTA, DSL, 
        "TOYOTA", "Land Cruiser 200\n\
        Land Cruiser 300\n\
        Toyota Camry 55",
        "Далее", "Отмена"
    );
    return 1;
}

DIALOG_KITAY(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:CAR_KITAY, DSL, 
        "Китай", "ZEEKR 001\n\
        LI9",
        "Далее", "Отмена"
    );
    return 1;
}

DIALOG_MYSORA(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:CAR_MYSORA, DSL, 
        "Полиция", "Skoda Octavia (ДПС)",
        "Далее", "Отмена"
    );
    return 1;
}

DIALOG_PORSCHE(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:CAR_PORSCHE, DSL, 
        "Porsche", "Cayenne",
        "Далее", "Отмена"
    );
    return 1;
}

DIALOG_MERCEDES(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:CAR_MERCEDES, DSL, 
        "Mercedes",
        "CLS55\n\
        E55AMG\n\
        E63S\n\
        G63\n\
        W140\n\
        W204\n\
        W211\n\
        W212\n\
        W218\n\
        W221\n\
        W223", 
        "Далее", "Отмена"
    );
    return 1;
}

DIALOG_BMW(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:CAR_BMW, DSL, 
        "BMW",
        "E34\n\
        E60\n\
        E92\n\
        G82\n\
        M5 F90\n\
        M6\n\
        X5\n\
        M8\n\
        M4 F82\n\
        M5 F10",
        "Далее", "Отмена"
    );
    return 1;
}

DIALOG_BIKES(playerid)
{
    Dialog_Open
    (
        playerid, Dialog:CAR_BIKES, DSL, 
        "Bikes",
        "BMW\n\
        Ducati", 
        "Далее", "Отмена"
    );
    return 1;
}

// ............. [ COMMANDS ] .............
CMD:car(playerid)
{
    DIALOG_CAR(playerid);
    return 1;
}

// ............. [ RESPONSES ] .............
Dialog_Response:CAR_LIST(playerid, response, listitem)
{
    if (!response) {
        return 1;
    }

    switch (listitem) {
        case 0: DIALOG_VAZ(playerid);
        case 1: DIALOG_MERCEDES(playerid);
        case 2: DIALOG_BMW(playerid);
        case 3: DIALOG_TOYOTA(playerid);
        case 4: DIALOG_LEXUS(playerid);
        case 5: DIALOG_PORSCHE(playerid);
        case 6: DIALOG_KITAY(playerid);
        case 7: DIALOG_BIKES(playerid);
        case 8: DIALOG_MYSORA(playerid);
    }
    return 1;
}

Dialog_Response:CAR_VAZ(playerid, response, listitem)
{
    if (!response) {
        return 1;
    }

    new vehicleID;
    switch (listitem) {
        case 0: vehicleID = 492; // Greenwood (2101)
        case 1: vehicleID = 422; // Bobcat (2105)
        case 2: vehicleID = 479; // Regina (2106)
        case 3: vehicleID = 442; // Romero (2109)
        case 4: vehicleID = 491; // Virgo (2110)
        case 5: vehicleID = 549; // Tampa (2112)
        case 6: vehicleID = 543; // Sadler (2114)
        case 7: vehicleID = 404; // Peren (Granta)
        case 8: vehicleID = 410; // Manana (Priora)
    }
    SpawnPlayerVehicle(playerid, vehicleID);
    return 1;
}

Dialog_Response:CAR_TOYOTA(playerid, response, listitem)
{
    if (!response) {
        return 1;
    }

    new vehicleID;
    switch (listitem) {
        case 0: vehicleID = 579; // Greenwood (2101)
        case 1: vehicleID = 400; // Bobcat (2105)
        case 2: vehicleID = 507; // Regina (2106)
    }
    SpawnPlayerVehicle(playerid, vehicleID);
    return 1;
}

Dialog_Response:CAR_MYSORA(playerid, response, listitem)
{
    if (!response) {
        return 1;
    }

    new vehicleID;
    switch (listitem) {
        case 0: vehicleID = 596; // Greenwood (2101)
    }
    SpawnPlayerVehicle(playerid, vehicleID);
    return 1;
}

Dialog_Response:CAR_PORSCHE(playerid, response, listitem)
{
    if (!response) {
        return 1;
    }

    new vehicleID;
    switch (listitem) {
        case 0: vehicleID = 411; // Greenwood (2101)
    }
    SpawnPlayerVehicle(playerid, vehicleID);
    return 1;
}

Dialog_Response:CAR_LEXUS(playerid, response, listitem)
{
    if (!response) {
        return 1;
    }

    new vehicleID;
    switch (listitem) {
        case 0: vehicleID = 489; // Greenwood (2101)
        case 1: vehicleID = 559; // Bobcat (2105)
    }
    SpawnPlayerVehicle(playerid, vehicleID);
    return 1;
}

Dialog_Response:CAR_KITAY(playerid, response, listitem)
{
    if (!response) {
        return 1;
    }

    new vehicleID;
    switch (listitem) {
        case 0: vehicleID = 451; // Greenwood (2101)
        case 1: vehicleID = 415; // Bobcat (2105)
    }
    SpawnPlayerVehicle(playerid, vehicleID);
    return 1;
}

Dialog_Response:CAR_MERCEDES(playerid, response, listitem)
{
    if (!response) {
        return 1;
    }

    new vehicleID;
    switch (listitem) {
        case 0: vehicleID = 467; // Oceanic (CLS55)
        case 1: vehicleID = 458; // Solair (E55AMG)
        case 2: vehicleID = 558; // Uranus (E63S)
        case 3: vehicleID = 602; // Alpha (G63)
        case 4: vehicleID = 436; // Previon (W140)
        case 5: vehicleID = 527; // Cadrona (W204)
        case 6: vehicleID = 587; // Euros (W211)
        case 7: vehicleID = 551; // Merit (W212)
        case 8: vehicleID = 541; // Bullet (W218)
        case 9: vehicleID = 535; // Slamvan (W221)
        case 10: vehicleID = 545; // Hustler (W223)
    }
    SpawnPlayerVehicle(playerid, vehicleID);
    return 1;
}

Dialog_Response:CAR_BMW(playerid, response, listitem)
{
    if (!response) {
        return 1;
    }

    new vehicleID;
    switch (listitem) {
        case 0: vehicleID = 412; // Voodoo (E34)
        case 1: vehicleID = 474; // Hermes (E60)
        case 2: vehicleID = 475; // Sabre (E92)
        case 3: vehicleID = 542; // Clover (G82)
        case 4: vehicleID = 567; // Savanna (M5F90)
        case 5: vehicleID = 439; // Stallion (M6)
        case 6: vehicleID = 402; // X5
        case 7: vehicleID = 516; // M8
        case 8: vehicleID = 518; // f82
        case 9: vehicleID = 536; // f10
    }
    SpawnPlayerVehicle(playerid, vehicleID);
    return 1;
}

Dialog_Response:CAR_BIKES(playerid, response, listitem)
{
    if (!response) {
        return 1;
    }

    new vehicleID;
    switch (listitem) {
        case 0: vehicleID = 521; // FCR900 (BMW)
        case 1: vehicleID = 522; // NRG500 (Ducati)
    }
    SpawnPlayerVehicle(playerid, vehicleID);
    return 1;
}

// ............. [ STOCKS ] .............
SpawnPlayerVehicle(playerid, vehicleID)
{
    if (IsPlayerConnected(playerid))
    {
        if (playerVehicleID[playerid] != 0 && IsValidVehicle(playerVehicleID[playerid]))
        {
            DestroyVehicle(playerVehicleID[playerid]);
            playerVehicleID[playerid] = 0;
        }
    }

    new Float:x, Float:y, Float:z, Float:angle;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, angle);

    new color1 = random(256);
    new color2 = random(256);

    new vehicleIDm = AddStaticVehicleEx(vehicleID, x, y, z, angle, color1, color2, 0);
    if (vehicleIDm != INVALID_VEHICLE_ID)
    {
        playerVehicleID[playerid] = vehicleIDm;
        SetVehicleParamsEx(vehicleIDm, 1, 1, 0, 0, 0, 0, 0);
        PutPlayerInVehicle(playerid, vehicleIDm, 0);
        SendClientMessage(playerid, -1, ""SC"Для установки тюнинга используйте {ffff00}/tune");
    }
    else
    {
        SCM(playerid, color_white, ""USC"не удалось создать транспортное средство.");
    }

    return 1;
}

// ............. [ HOOKS ] .............
hook OnPlayerDisconnect(playerid, reason)
{
    if (playerVehicleID[playerid] != 0 && IsValidVehicle(playerVehicleID[playerid]))
    {
        DestroyVehicle(playerVehicleID[playerid]);
        playerVehicleID[playerid] = 0; 
    }
    return 1;
}