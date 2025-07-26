#include <YSI_Coding\y_hooks>

// ............. [ DEFINES ] .............
#define SPD ShowPlayerDialog
#define DSL DIALOG_STYLE_LIST
#define SC "{ffff00}| {ffffff}"
#define USC "{ff2400}| {ffffff}"

#if !defined color_white
    #define color_white 0xffffffAA
#endif

#if !defined color_gray
    #define color_gray 0x999999AA
#endif

CMD:askin(playerid)
{
    if(GetPlayerAdminEx(playerid) < 1) return 1;

    if(!isAdminSkin[playerid])
    {
        SetPlayerSkin(playerid, 122);
        SendClientMessage(playerid, color_white, ""SC"Вы успешно надели скин администратора.");
        isAdminSkin[playerid] = true;
    } else {
        SetPlayerSkin(playerid, GetPlayerData(playerid, pSkin));
        SendClientMessage(playerid, color_white, ""SC"Вы сняли скин администратора.");
        isAdminSkin[playerid] = false;
    }
}

CMD:az(playerid)
{
    if(GetPlayerAdminEx(playerid) < 1) return 1;

    SetPlayerInterior(playerid, 12);
    SetPlayerPos(playerid, 2324.38, -1148.48, 1050.71);
    SendClientMessage(playerid, color_white, ""SC"вы успешно телепортировались в админ-зону.");
    return 1;
}

CMD:getid(playerid)
{
    new message[64];
    format(message, sizeof(message), "ID: %d", player_info[playerid][pId]);


    SendClientMessage(playerid, -1, message);

    return 1;
}

CMD:vget(playerid, params[])
{
	if (player_info[playerid][pAdmin] < 2)
        return 1;

	extract params -> new vehicleid; else return SendClientMessage(playerid, color_white, ""USC"Введите: "c_lightyellow"/vget [id транспорта]");
	if(!IsValidVehicle(vehicleid)) return SendClientMessage(playerid, color_white, ""USC"Данного транспорта не существует на сервере.");

	new Float: x, Float: y, Float: z;
	GetPlayerPos(playerid, x, y, z);

	SetVehiclePos(vehicleid, x + 2.0, y + 2.0, z);

	SendClientMessage(playerid, color_white, ""SC"Вы телепортировали авто к себе.");

	new fmt_msg[105];

	format(fmt_msg, sizeof fmt_msg, "Телепортировался к себе авто №%d", vehicleid);
	SendLog(playerid, LOG_TYPE_ADMIN_ACTION, fmt_msg);

    format(fmt_msg, sizeof(fmt_msg), "[A] %s %s[%d] телепортировал к себе авто №%d", player_info[playerid][pPrefix], player_info[playerid][pName], playerid,  vehicleid);
    AdmMSG(color_gray, fmt_msg);
		
	return 1;
}

CMD:slap(playerid, params[])
{
    if (player_info[playerid][pAdmin] < 1)
        return 1;

    new target_id;

    if (sscanf(params, "i", target_id))
        return SendClientMessage(playerid, color_white, ""USC"Введите: "c_lightyellow"/slap [id игрока]");

    if (!IsPlayerConnected(target_id))
        return SendClientMessage(playerid, color_red, ""USC"Такого игрока нет.");

    new Float:x, Float:y, Float:z;
    GetPlayerPos(target_id, x, y, z);

    SetPlayerPos(target_id, x, y, z + 5.0);
    PlayerPlaySound(target_id, 1130, 0.0, 0.0, 0.0);

    new fmt_msg[128];
    format(fmt_msg, sizeof(fmt_msg), "[A] %s %s[%d] подбросил игрока %s[%i]", player_info[playerid][pPrefix], player_info[playerid][pName], playerid, player_info[target_id][pName], target_id);
    AdmMSG(color_gray, fmt_msg);

    SendClientMessage(target_id, color_blue, "Вас подбросил администратор!");

    return 1;
}

CMD:ban(playerid, params[])
{
    if (player_info[playerid][pAdmin] < 2) 
        return 1;

    new targetID, ban_time;
    new string:reason[64];

    if (sscanf(params, "i[8] i[8] s[64]", targetID, ban_time, reason)) {
        return SendClientMessage(playerid, color_red, ""USC"Введите: "c_lightyellow"/ban [ID игрока] [длительность] [причина]");
    }

    if (targetID < 0 || targetID >= MAX_PLAYERS || !IsPlayerConnected(targetID)) {
        return SendClientMessage(playerid, color_red, ""USC"Игрок с таким ID не найден.");
    }

    new max_days = player_info[playerid][pAdmin] < 3 ? 365 : 30;
    new fmt_msg[128];

    if (!(1 <= ban_time && ban_time <= max_days))
    {
        format(fmt_msg, sizeof(fmt_msg), ""USC"Срок бана может быть от 1 до %d дней", max_days);
        return SendClientMessage(playerid, color_red, fmt_msg);
    }

    if (player_info[targetID][pAdmin] > player_info[playerid][pAdmin])
        return SendClientMessage(playerid, color_red, ""USC"Вы не можете забанить администратора с более высоким рангом.");

    if (targetID == playerid)
        return SendClientMessage(playerid, -1, ""USC"Вы не можете забанить самих себя.");

    format(fmt_msg, sizeof(fmt_msg), "Администратор %s забанил игрока %s на %d дней", player_info[playerid][pName], player_info[targetID][pName], ban_time);

    if (strlen(reason) > 0)
        format(fmt_msg, sizeof(fmt_msg), "%s. Причина: %s", fmt_msg, reason);

    SCMTA(color_red, fmt_msg);

    new str1[128];
    format(str1, sizeof(str1), "[A] %s %s[%i] забанил игрока %s", player_info[playerid][pPrefix], player_info[playerid][pName], playerid, player_info[targetID][pName]);
    AdmMSG(color_gray, str1);

    if (!strlen(reason)) reason = "Не указана";

    format(fmt_msg, sizeof(fmt_msg), "Забанен %s[acc:%d] на %d дней. Причина: %s", player_info[targetID][pName], player_info[targetID][pId], ban_time, reason);
    SendLog(playerid, LOG_TYPE_SUPERADMIN_ACTION, fmt_msg);

    AddBan(player_info[targetID][pId], gettime(), ban_time, reason, player_info[playerid][pId]);

    Kick(targetID); 
    
    UpdateAdminStat(playerid, "ban");

    return 1;
}

CMD:getip(playerid, params[])
{

    if (player_info[playerid][pAdmin] < 2) return 1;

    new targetID;
    if (sscanf(params, "i[8]", targetID))
        return SendClientMessage(playerid, color_red, ""USC"Введите: "c_lightyellow"/getip [ID игрока]");

    if (targetID < 0 || targetID >= MAX_PLAYERS || !IsPlayerConnected(targetID))
        return SendClientMessage(playerid, color_red, ""USC"Игрок с таким ID не найден.");

    new ip[16];
    GetPlayerIp(targetID, ip, sizeof(ip));

    new msg[128];
    format(msg, sizeof(msg), "IP-адрес игрока %s: %s", player_info[targetID][pName], ip);
    SendClientMessage(playerid, color_green, msg);

    return 1;
}

CMD:banip(playerid, params[])
{
    if (player_info[playerid][pAdmin] < 2) return 1;


    new ip[16];
    if (sscanf(params, "s[15]", ip))
        return SendClientMessage(playerid, color_red, ""USC"Введите: "c_lightyellow"/banip [IP-адрес]");


    new query[128];
    format(query, sizeof(query), "banip %s", ip);
    SendRconCommand(query);

    SendRconCommand("reloadbans");

    new log_msg[128];
    format(log_msg, sizeof(log_msg), "Администратор %s заблокировал IP %s", player_info[playerid][pName], ip);
    SCMTA(color_red, log_msg);
    SendLog(playerid, LOG_TYPE_SUPERADMIN_ACTION, log_msg);
    
    UpdateAdminStat(playerid, "ban");

    return 1;
}

CMD:unban(playerid, params[])
{
	if (player_info[playerid][pAdmin] < 2) return 1;

	if (!strlen(params))
        return SendClientMessage(playerid, color_white, ""USC"Введите: "c_lightyellow"/unban [ник игрока]");

    new player_name[21];
    sscanf(params, "s[64]", player_name); 

	new query[80],
		Cache: result,
		rows,
		uid,
		uip[16];

	mysql_format(dbHandle, query, sizeof query, "SELECT id FROM accounts WHERE name='%s'", player_name);
	result = mysql_query(dbHandle, query, true);

	rows = cache_num_rows();

	if(rows)
	{
		uid = cache_get_row_int(0, 0);
		cache_get_row(0, 1, uip);
	}

	cache_delete(result);

	if(!rows || !uid) return SendClientMessage(playerid, color_red, ""USC"Игрок с таким именем не найден");

	mysql_format(dbHandle, query, sizeof query, "SELECT * FROM ban_list WHERE user_id=%d", uid);
	result = mysql_query(dbHandle, query, true);

	rows = cache_num_rows();

	cache_delete(result);

	if(!rows) return SendClientMessage(playerid, color_red, ""USC"Аккаунт игрока не заблокирован");

	mysql_format(dbHandle, query, sizeof query, "DELETE FROM ban_list WHERE user_id=%d", uid);
	mysql_query(dbHandle, query, false);

	format(query, sizeof query, "unbanip %s", uip);
	SendRconCommand(query);

	SendRconCommand("reloadbans");

	new str[128];
    format(str, sizeof(str), "Администратор %s разбанил игрока %s", player_info[playerid][pName], player_name);
    SCMTA(color_red, str);

	format(query, sizeof query, "Разбанил %s[acc:%d]", player_name, uid);
	SendLog(playerid, LOG_TYPE_SUPERADMIN_ACTION, query);

	return 1;
}

CMD:spermban(playerid, params[])
{
    if (player_info[playerid][pAdmin] < 3)
        return 1;

    if (!strlen(params))
        return SendClientMessage(playerid, color_white, ""USC"Введите команду: "c_lightyellow"/spermban [ник игрока] [причина]");

    new to_player;
    new string:reason[64]; 


    new paramsString[128];
    sscanf(params, "s[64] s[64]", paramsString, reason); 


    to_player = GetPlayerIDByName(paramsString);
    if (to_player == -1)
        return SendClientMessage(playerid, color_gray, "Игрок с таким ником не найден.");


    if (player_info[to_player][pAdmin] > player_info[playerid][pAdmin])
        return SendClientMessage(playerid, color_gray, "Вы не можете забанить администратора с большим рангом.");

    if (to_player == playerid)
        return SendClientMessage(playerid, color_gray, "Вы не можете забанить самих себя.");


    new fmt_msg[128];
    format(fmt_msg, sizeof(fmt_msg), "Администратор %s забанил игрока %s.", player_info[playerid][pName], player_info[to_player][pName]);

    if (strlen(reason) > 0)
        format(fmt_msg, sizeof(fmt_msg), "%s Причина: %s", fmt_msg, reason);

    SCMTA(color_red, fmt_msg);

    new str1[128];
    format(str1, sizeof(str1), "[A] %s %s[%i] забанил игрока %s.", player_info[playerid][pPrefix], player_info[playerid][pName], playerid, player_info[to_player][pName]);
    AdmMSG(color_gray, str1);

    if (!strlen(reason)) reason = "Не указана";

    format(fmt_msg, sizeof(fmt_msg), "Забанен игрок %s[acc:%d]. Причина: %s", player_info[to_player][pName], player_info[to_player][pId], reason);
    SendLog(playerid, LOG_TYPE_SUPERADMIN_ACTION, fmt_msg);

    AddBan(player_info[to_player][pId], gettime(), 1000, reason, player_info[playerid][pId]);

    
    UpdateAdminStat(playerid, "ban");

    Kick(to_player);
    return 1;
}

CMD:mute(playerid, params[])
{
    if (player_info[playerid][pAdmin] < 1)
        return 1;

    new targetID, mute_duration, string:reason[64];
    if (sscanf(params, "i[8] i[8] s[64]", targetID, mute_duration, reason)) {
        SendClientMessage(playerid, color_gray, ""USC"Введите: "c_lightyellow"/mute [ID] [длительность] [причина]");
        return 1;
    }

    if (mute_duration < 1 || mute_duration > MAX_MUTE_DURATION) {
        SendClientMessage(playerid, color_gray, ""USC"Длительность мута должна быть от 1 до 60 минут.");
        return 1;
    }

    if (targetID < 0 || targetID >= MAX_PLAYERS || !IsPlayerConnected(targetID)) {
        SendClientMessage(playerid, color_gray, ""USC"Игрок с таким ID не найден.");
        return 1;
    }

    if (player_info[targetID][pMute] == 1) {
        SendClientMessage(playerid, color_gray, ""USC"У игрока уже есть мут.");
        return 1;
    }

    UpdatePlayerDatabaseInt(targetID, "Mute", mute_duration * 60);
    player_info[targetID][pMute] = mute_duration * 60;

    new fmt_msg[256];
    format(fmt_msg, sizeof(fmt_msg), "Администратор %s замутил игрока %s на %d минут. Причина: %s", player_info[playerid][pName], player_info[targetID][pName], mute_duration, reason);
    SCMTA(color_red, fmt_msg);

    format(fmt_msg, sizeof(fmt_msg), "Администратор %s[acc:%d] замутил игрока %s на %d минут. Причина: %s", player_info[playerid][pName], player_info[playerid][pId], player_info[targetID][pName], mute_duration, reason);
    SendLog(playerid, LOG_TYPE_ADMIN_ACTION, fmt_msg);
    
    UpdateAdminStat(playerid, "mute");
    
    return 1;
}

CMD:unmute(playerid, params[])
{
    if (player_info[playerid][pAdmin] < 1) return 1;

    new playerName[32];
    if (sscanf(params, "s[32]", playerName)) {
        SendClientMessage(playerid, color_white, ""USC"Введите: "c_lightyellow"/unmute [ник игрока]");
        return 1;
    }

    new to_player = GetPlayerIDByName(playerName);
    if (to_player == -1) {
        SendClientMessage(playerid, color_red, ""USC"Игрок с таким ником не найден.");
        return 1;
    }

    if (player_info[to_player][pMute] == 0) {
        SendClientMessage(playerid, color_red, ""USC"Игрок не замучен.");
        return 1;
    }

    UpdatePlayerDatabaseInt(to_player, "Mute", 0);
    player_info[to_player][pMute] = 0;

    new fmt_msg[128];
    format(fmt_msg, sizeof(fmt_msg), "Администратор %s размутил игрока %s", player_info[playerid][pName], player_info[to_player][pName]);
    SCMTA(color_red, fmt_msg);

    SendClientMessage(to_player, color_gray, "Доступ в чат восстановлен.");

    format(fmt_msg, sizeof(fmt_msg), "Снял блокировку чата у %s[acc:%d]", player_info[to_player][pName], player_info[to_player][pId]);
    SendLog(playerid, LOG_TYPE_ADMIN_ACTION, fmt_msg);

    return 1;
}

CMD:kick(playerid, params[])
{
    if (player_info[playerid][pAdmin] < 1)
        return 1;

    new to_player, reason[30];

    if (sscanf(params, "i s[30]", to_player, reason))
        return SendClientMessage(playerid, color_white, ""USC"Введите: "c_lightyellow"/kick [id игрока] [причина]");

    if (!IsPlayerConnected(to_player))
        return SendClientMessage(playerid, color_red, ""USC"Такого игрока нет.");

    new fmt_msg[128];
    format(fmt_msg, sizeof fmt_msg, "Администратор %s кикнул игрока %s. Причина: %s", player_info[playerid][pName], player_info[to_player][pName], reason);
    SCMTA(color_red, fmt_msg);

    format(fmt_msg, sizeof fmt_msg, "Кикнул %s[acc:%d]. Причина: %s", player_info[to_player][pName], player_info[to_player][pId], reason);
    SendLog(playerid, LOG_TYPE_ADMIN_ACTION, fmt_msg);

    Kick(to_player);
    
    UpdateAdminStat(playerid, "kick");

    return 1;
}

CMD:techrest(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 8) 
    {
        SendClientMessage(playerid, color_red, "У вас недостаточно прав для использования этой команды.");
        return 1;
    }

    for (new i = 0; i < 5; i++) {
        SCMTA(color_red, " "); 
    }

    SCMTA(color_red, "Технический рестарт начнется через 1 минуту!");
    SCMTA(color_red, "Технический рестарт начнется через 1 минуту!");
    SCMTA(color_red, "Технический рестарт начнется через 1 минуту!");
    SCMTA(color_red, "Технический рестарт начнется через 1 минуту!");
    SCMTA(color_red, "Технический рестарт начнется через 1 минуту!");

    SetTimerEx("TechRestartTimer", 60000, false, "d", playerid); 

    return 1;
}

CMD:astats(playerid, params[])
{
	if(login_check[playerid] == false) return 1; // во избежания дюпа
    if(GetPlayerAdminEx(playerid) < 1) return 1;

    new dialog[512];
    format(dialog, sizeof(dialog), "1. Баны: %d\n\
                                   2. Муты: %d\n\
                                   3. Кики: %d\n\
                                   4. Преды: %d",
						           AdminStats[playerid][bans],
						           AdminStats[playerid][mutes],
						           AdminStats[playerid][kicks],
						           AdminStats[playerid][warns]);

    SPD(playerid, d_none, DSL, "{3FD7D0}LIT {FFFFFF}| СТАТИСТИКА", dialog, "Закрыть", "");
    return 1;
}

CMD:setwlist(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 8) return 1;
    static const fmt_str[] = "";
    new string[sizeof(fmt_str) + MAX_PLAYER_NAME],d_nick[MAX_PLAYER_NAME];

    if(sscanf(params, "s[24]", d_nick)) return SendClientMessage(playerid, -1, "Используйте: /setwlist [ник игрока]");

    mysql_format(dbHandle, string, sizeof(string), "SELECT * FROM whitelist WHERE name = '%s'", d_nick);
    new Cache:result = mysql_query(dbHandle, string);

    if(cache_num_rows())
    {
        SendClientMessage(playerid, -1, "Этот игрок уже внесён в вайт лист");
    }
    else
    {
        new string[999];

        new fmt_str[999];


        mysql_format(dbHandle, string, sizeof(string), "INSERT INTO whitelist (name) VALUES ('%s')", d_nick);
        mysql_tquery(dbHandle, string);

        format(string, sizeof(string), fmt_str, d_nick);
        SendClientMessage(playerid, -1, string);
    }

    cache_delete(result);
    return 1;
}

CMD:dellwlist(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 8) return 1;
    static const fmt_str[] = "";
    new string[sizeof(fmt_str) + MAX_PLAYER_NAME],d_nick[MAX_PLAYER_NAME];

    if(sscanf(params, "s[32]", d_nick)) return SendClientMessage(playerid, -1, !"Используйте: /dellwlist [ник игрока]");

    mysql_format(dbHandle, string, sizeof(string), "SELECT * FROM whitelist WHERE name = '%s'", d_nick);
    new Cache:result = mysql_query(dbHandle, string);

    if(cache_num_rows())
    {
        new string[999];

        new fmt_str[999];

        mysql_format(dbHandle, string, sizeof(string), "DELETE FROM whitelist WHERE name = '%s'", d_nick);
        mysql_tquery(dbHandle, string);

        format(string, sizeof(string), fmt_str, d_nick);
        SendClientMessage(playerid, -1, string);
    }
    else
    {
        SendClientMessage(playerid, color_red, !"данного акка нет в вл");
    }

    cache_delete(result);
    return 1;
}

CMD:flip(playerid)
{
	if(GetPlayerAdminEx(playerid) < 1) return 1;
	
	new vehicleid = GetPlayerVehicleID(playerid);

    if(vehicleid == 0)
    {
            SendClientMessage(playerid, -1, "Вы должны сидеть в транспорте!");
            return 0;
    }

    new Float:x, Float:y, Float:z;
    new Float:angle;


    GetVehiclePos(vehicleid, x, y, z);
    GetVehicleZAngle(vehicleid, angle);


    SetVehiclePos(vehicleid, x, y, z + 1.5);
    SetVehicleZAngle(vehicleid, angle);

    SendClientMessage(playerid, -1, "Вы успешно поставили транспорт на колёса и починили его!");
        
	RepairVehicle(vehicleid);
	SetVehicleHealth(vehicleid,1000);
	
	return 1;
}

CMD:veh(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 5) return 1;

    new vehicleID, color1, color2;
    if (sscanf(params, "iii", vehicleID, color1, color2))
        return SendClientMessage(playerid, -1, ""USC"Введите: "c_lightyellow"/veh [id т/с] [color1] [color2]");

    if (vehicleID < 400 || vehicleID > 3000 || color1 < 0 || color1 > 255 || color2 < 0 || color2 > 255)
        return SendClientMessage(playerid, 0xbfbfbfff, ""USC"ID т/с: 400-3000, цвет: 0-255.");

    new Float:x, Float:y, Float:z, Float:rot;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, rot);


    new vehID = AddStaticVehicleEx(vehicleID, x, y, z, rot, color1, color2, -1);
    if (!vehID) return SendClientMessage(playerid, 0xbfbfbfff, ""USC"Ошибка при создании Т/С.");


    playerCreatedVehicleID[playerid] = vehID;

    PutPlayerInVehicle(playerid, vehID, 0);
    SetVehicleParamsEx(vehID, 1, 1, 0, 0, 0, 0, 0);

    new msg[128];
    format(msg, sizeof(msg), "[A] %s %s[%i] создал т/с [%d, %d, %d]", player_info[playerid][pPrefix], player_info[playerid][pName], playerid, vehicleID, color1, color2);
    AdmMSG(color_gray, msg);

    SendLog(playerid, LOG_TYPE_ADMIN_ACTION, msg);
    return SendClientMessage(playerid, -1, ""SC"Транспортное средство успешно создано.");
}

CMD:setadm(playerid, params[])
{
    if (GetPlayerAdminEx(playerid) < 5) return 1;

    new targetID, adminLevel;
    new targetName[MAX_PLAYER_NAME];

    if (sscanf(params, "si", targetName, adminLevel))
        return SendClientMessage(playerid, color_red, ""USC"Введите: "c_lightyellow"/setadm [ник игрока] [уровень]");

    if (adminLevel < 0 || adminLevel > 5)
        return SendClientMessage(playerid, color_red, ""USC"Неверный уровень админки (0-5).");

    targetID = GetPlayerByName(targetName);
    if (targetID == -1)
    {
        if (!UpdatePlayerDatabaseIntByName(targetName, "admin", adminLevel))
            return SendClientMessage(playerid, color_red, ""USC"Игрок с таким ником не найден.");

        new prefix[16];
        AdmPreff(adminLevel, prefix, sizeof(prefix));

        UpdatePlayerDatabaseStrByName(targetName, "prefix", prefix); 

        new msg[128];
        format(msg, sizeof(msg), "[A] %s %s[%i] установил админ уровень %d для игрока %s (оффлайн).", 
            player_info[playerid][pPrefix], player_info[playerid][pName], playerid, adminLevel, targetName);
        AdmMSG(color_gray, msg);

        SendLog(playerid, LOG_TYPE_SET_ADMIN, msg);
        return 1;
    }

    player_info[targetID][pAdmin] = adminLevel;

    new prefix[16];
    AdmPreff(adminLevel, prefix, sizeof(prefix));

    format(GetPlayerData(targetID, pPrefix), 15, prefix);
    
    UpdatePlayerDatabaseStr(targetID, "prefix", prefix); 

    new msg[128];
    format(msg, sizeof(msg), "[A] %s %s[%i] выдал админ права %d уровня игроку %s[%d]", 
        player_info[playerid][pPrefix], player_info[playerid][pName], playerid, adminLevel, player_info[targetID][pName], targetID);
    AdmMSG(color_gray, msg);

    UpdatePlayerDatabaseInt(targetID, "admin", adminLevel);
    SendLog(playerid, LOG_TYPE_SET_ADMIN, msg);

    return 1;
}

CMD:spawn(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 1) return 1;

    new targetid;
    if (sscanf(params, "u", targetid))
        return SendClientMessage(playerid, color_red, ""USC"Введите: "c_lightyellow"/spawn [id игрока]");

    if (!IsPlayerConnected(targetid))
        return SendClientMessage(playerid, color_red, ""USC"Игрок с таким ID не подключен.");

    new msg[128];
    format(msg, sizeof(msg), "[A] %s %s[%i] заспавнил игрока %s[%i]", player_info[playerid][pPrefix], player_info[playerid][pName], playerid, player_info[targetid][pName], targetid);
    AdmMSG(color_gray, msg);
    SendLog(playerid, LOG_TYPE_ADMIN_ACTION, msg);

    SetPlayerSpawn(targetid);
    return 1;
}

CMD:a(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 1) return 1;

    if (sscanf(params, "s[144]", params)) return SendClientMessage(playerid, color_white, ""USC"Введите: "c_lightyellow"/a [текст]");
    if (strlen(params) > 104) return SendClientMessage(playerid, color_red, ""USC"Слишком длинное сообщение!");

    new playerName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, playerName, sizeof(playerName));

    new fmt_str[256];
    format(fmt_str, sizeof(fmt_str), "%s %s[%d]: %s", player_info[playerid][pPrefix], playerName, playerid, params);

    AdmMSG(color_achat, fmt_str);
    SendLog(playerid, LOG_TYPE_ADMIN_CHAT, fmt_str);

    return 1;
}

CMD:givecash(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 5) return 1;

    new targetID, amount;
    if (sscanf(params, "ui", targetID, amount) || amount < 1 || amount > 100000000 || !IsPlayerConnected(targetID))
        return SendClientMessage(playerid, color_red, ""USC"Введите: "c_lightyellow"/givemoney [id игрока] [деньги 1-100000000]");

    GivePlayerCash(targetID, amount);

    new msg[128];
    format(msg, sizeof(msg), "[A] %s %s[%i] выдал %i$ игроку %s[%i]", player_info[playerid][pPrefix], player_info[playerid][pName], playerid, amount, player_info[targetID][pName], targetID);
    AdmMSG(color_gray, msg);

    SendLog(playerid, LOG_TYPE_SUPERADMIN_ACTION, msg);
    return 1;
}

CMD:setweather(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 5) return 1;
    
    if (sscanf(params, "i", params[0]))
    {
        SendClientMessage(playerid, color_white, ""USC"Введите: "c_lightyellow"/setweather [погода (0-20)]");
        return 1;
    }

    if (params[0] < 0 || params[0] > 45)
    {
        SendClientMessage(playerid, color_white, "Уровень погоды должен быть от 0 до 20.");
        return 1;
    }

    SetWeather(params[0]);

    new adminName[MAX_PLAYER_NAME];
    GetPlayerName(playerid, adminName, sizeof(adminName));
    new str2[128];
    format(str2, sizeof(str2), "[A] %s изменил погоду на %d.", adminName, params[0]);
    AdmMSG(color_gray, str2);
    
    format(str2, sizeof str2, "Установил погоду №%d на сервере", params[0]);
	SendLog(playerid, LOG_TYPE_ADMIN_ACTION, str2);

    return 1;
}

CMD:pos(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 1) return 1;
    
	new Float: x, Float: y, Float: z, interior, virtual_world;

	if(sscanf(params, "P<,>fff", x, y, z))
		return SendClientMessage(playerid, 0xCECECEFF, ""USC"Введите: "c_lightyellow"/pos [x y z]");

	sscanf(params, "P<,>{fff}dd", interior, virtual_world);

	return SetPlayerPos(playerid, x, y, z);
}

CMD:settime(playerid, params[])
{
	if(GetPlayerAdminEx(playerid) < 8) return 1;
	
	extract params -> new time; else return SendClientMessage(playerid, 0xCECECEFF, ""USC"Введите: "c_lightyellow"/settime [время 0-23]");

	if(!(0 <= time <= 23)) return SendClientMessage(playerid, 0x999999FF, ""USC"Время от 0 до 23 часов!");

	SetWorldTime(time);

	new fmt_text[70];

	format(fmt_text, sizeof fmt_text, "[A] %s %s[%i] установил время %02d:00 на сервере", player_info[playerid][pPrefix], player_info[playerid][pName], playerid, time);
	AdmMSG(color_gray, fmt_text);
	
	format(fmt_text, sizeof fmt_text, "Установил время %02d:00 на сервере", time);
	SendLog(playerid, LOG_TYPE_ADMIN_ACTION, fmt_text);

	return 1;
}

CMD:cc(playerid, params[])
{
	if(GetPlayerAdminEx(playerid) < 4) return 1;
	
	for(new i = 0; i < 20; i++)
	{
		SCMTA(-1, "");
	}

	SCMTA(color_yellow, "Чат был очищен администрацией");
	SendLog(playerid, LOG_TYPE_ADMIN_ACTION, "Очистил чат");
	return 1;
}

CMD:setskin(playerid, params[])
{
    new targetid, skinid;
    
    if(GetPlayerAdminEx(playerid) < 3) return 1;

    if(sscanf(params, "ud", targetid, skinid))
        return SendClientMessage(playerid, -1, ""USC"Введите: "c_lightyellow"/setskin [id игрока] [id скина]");

    if(!IsPlayerConnected(targetid))
        return SendClientMessage(playerid, -1, ""USC"Игрок с таким ID не подключен.");

    new fmt_text[128];

    SetPlayerSkin(targetid, skinid);
    player_info[targetid][pSkin] = skinid;
    UpdatePlayerDatabaseInt(targetid, "Skin", skinid);

    format(fmt_text, sizeof(fmt_text), "[A] %s %s[%i] установил скин игроку %s[%i]", player_info[playerid][pPrefix], player_info[playerid][pName], playerid, player_info[targetid][pName], targetid);
    AdmMSG(color_gray, fmt_text);
    
    format(fmt_text, sizeof fmt_text, "Установил %s[acc:%d] скин %d", player_info[targetid][pName], player_info[targetid][pId], skinid);
	SendLog(playerid, LOG_TYPE_ADMIN_ACTION, fmt_text);

    return 1;
}

CMD:givegun(playerid, params[])
{
    new targetid, weaponid, ammo;
    
    if(GetPlayerAdminEx(playerid) < 4) return 1;
    
    if(sscanf(params, "ddd", targetid, weaponid, ammo))
        return SendClientMessage(playerid, -1, ""USC"Введите: "c_lightyellow"/givegun [id игрока] [id оружия] [патроны]");

    if(!IsPlayerConnected(targetid))
        return SendClientMessage(playerid, -1, ""USC"Игрок с таким ID не подключен.");

    new fmt_text[128];

    GivePlayerWeapon(targetid, weaponid, ammo);
    format(fmt_text, sizeof(fmt_text), "[A] Администратор %s[%d] выдал %s[%d] %d [%d патрон]",
	player_info[playerid][pName], playerid, player_info[targetid][pName], targetid, weaponid, ammo);
    AdmMSG(color_gray, fmt_text);
    
    format(fmt_text, sizeof fmt_text, "Выдал %s[acc:%d] %s[%d патр]", player_info[targetid][pName], player_info[targetid][pId], weaponid, ammo);
	SendLog(playerid, LOG_TYPE_ADMIN_ACTION, fmt_text);

    return 1;
}

CMD:goto(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 1) return 1;
    
	extract params -> new to_player; else return SendClientMessage(playerid, color_white, !""USC"Введите: "c_lightyellow"/goto [id]");
	new Float:x, Float:y, Float:z;
	GetPlayerPos(to_player, x, y, z);
	new vw = GetPlayerVirtualWorld(to_player);
	new int = GetPlayerInterior(to_player);
	SetPlayerPos(playerid, x+1.0, y+1.0, z);
	SetPlayerVirtualWorld(playerid, vw);
	SetPlayerInterior(playerid, int);
	new str[144];
	format(str, sizeof(str), ""SC"Вы телепортировались к игроку %s[%i]", player_info[params[0]][pName]);
	
	new fmt_text[128];
	format(fmt_text, sizeof(fmt_text), "[A] Администратор %s[%d] телепортировался к %s[%d]",
	player_info[playerid][pName], playerid, player_info[to_player][pName], to_player);
    AdmMSG(color_gray, fmt_text);
	
	new fmt_msg[105];
    format(fmt_msg, sizeof fmt_msg, "Телепортировался к %s[acc:%d]", player_info[to_player][pName], player_info[to_player][pId]);
	SendLog(playerid, LOG_TYPE_ADMIN_ACTION, fmt_msg);
	
	return 1;
}

CMD:gethere(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 2) return 1;
    
    extract params -> new to_player; else return SendClientMessage(playerid, color_white, !""USC"Введите: "c_lightyellow"/gethere [id]");
    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    new vw = GetPlayerVirtualWorld(playerid);
    new int = GetPlayerInterior(playerid);
    SetPlayerPos(to_player, x+1.0, y+1.0, z);
    SetPlayerVirtualWorld(params[0], vw);
    SetPlayerInterior(to_player, int);
	new str[144];
	format(str, sizeof(str), ""SC"Администратор %s[%i] телепортировал Вас к себе", player_info[playerid][pName], playerid);
	SendClientMessage(to_player, color_white, str);
	
	new fmt_text[128];
	format(fmt_text, sizeof(fmt_text), "[A] Администратор %s[%d] телепортировал к себе %s[%d]",
	player_info[playerid][pName], playerid, player_info[to_player][pName], to_player);
    AdmMSG(color_gray, fmt_text);
	
	new fmt_msg[105];
    format(fmt_msg, sizeof fmt_msg, "Телепортировал к себе %s[acc:%d]", player_info[to_player][pName], player_info[to_player][pId]);
	SendLog(playerid, LOG_TYPE_ADMIN_ACTION, fmt_msg);
	
	return 1;
}

CMD:msg(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 3) return 1;

    new msg[144];
    if (sscanf(params, "s[144]", msg)) return SendClientMessage(playerid, color_white, ""USC"Введите: "c_lightyellow"/msg [текст]");

    new finalMsg[200];
    format(finalMsg, sizeof(finalMsg), "[Администратор] %s: %s", player_info[playerid][pName], msg);

    SendClientMessageToAll(color_yellow, finalMsg);

    return 1;
}

CMD:ahelp(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 1) return 1;

    new dialog[512];
    format(dialog, sizeof(dialog), "1. Модератор\n\
                                   2. Младший администратор\n\
                                   3. Администратор\n\
                                   4. Старший администратор\n\
                                   5. Главный администратор\n\
                                   6. Специальный администратор\n\
                                   7. Куратор\n\
                                   8. Основатель\n");

    SPD(playerid, d_ahelp, DSL, "{3FD7D0}LIT {FFFFFF}| СПРАВКА", dialog, "Выбрать", "Отмена");
    return 1;
}

CMD:sp(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 1) return 1;

    new to_player;
    if (sscanf(params, "u", to_player)) 
        return SendClientMessage(playerid, color_white, ""USC"Введите: "c_lightyellow"/sp [id игрока]");

    if (!IsPlayerConnected(to_player))
        return SendClientMessage(playerid, 0x999999FF, "Такого игрока нет");


    if (GetPlayerAdminEx(playerid) < 5 && GetPlayerAdminEx(to_player) >= 5)
    {
		new fmt_text[90];
		format(fmt_text, sizeof fmt_text, "[A] Администратор %s[%d] попытался проследить за %s[%d]", player_info[playerid][pName], playerid, player_info[to_player][pName], to_player);
    AdmMSG(color_gray, fmt_text);
        return SendClientMessage(playerid, 0x999999FF, "Вы не можете следить за игроками уровня 5 и выше.");
    }

    if (GetPlayerSpectateData(playerid, S_PLAYER) == -1)
    {
        new Float:x, Float:y, Float:z, Float:a, skin = GetPlayerSkin(playerid);
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);

        SetPlayerSpectateData(playerid, S_START_POS_X, x);
        SetPlayerSpectateData(playerid, S_START_POS_Y, y);
        SetPlayerSpectateData(playerid, S_START_POS_Z, z);
        SetPlayerSpectateData(playerid, S_START_ANGLE, a);

        SetPlayerSpectateData(playerid, S_START_INTERIOR, GetPlayerInterior(playerid));
        SetPlayerSpectateData(playerid, S_START_VIRTUAL_WORLD, GetPlayerVirtualWorld(playerid));

        SetSpawnInfo(playerid, 0, skin, x, y, z, a, 0, 0, 0, 0, 0, 0);
    }

    StartSpectate(playerid, to_player);

    new fmt_text[90];
    format(fmt_text, sizeof fmt_text, "[A] Администратор %s[%d] следит за %s[%d]", player_info[playerid][pName], playerid, player_info[to_player][pName], to_player);
    AdmMSG(color_gray, fmt_text);

    format(fmt_text, sizeof fmt_text, "Следит за %s[acc:%d]", player_info[to_player][pName], player_info[to_player][pId]);
    SendLog(playerid, LOG_TYPE_ADMIN_ACTION, fmt_text);

    return 1;
}

CMD:asp(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 1) return 1;

    new to_player;
    if (sscanf(params, "u", to_player)) 
        return SendClientMessage(playerid, color_white, ""USC"Введите: "c_lightyellow"/asp [id игрока]");

    if (!IsPlayerConnected(to_player))
        return SendClientMessage(playerid, 0x999999FF, "Такого игрока нет");


    if (GetPlayerAdminEx(playerid) < 5 && GetPlayerAdminEx(to_player) >= 5)
    {
		new fmt_text[248];
		format(fmt_text, sizeof fmt_text, "[A] Администратор %s[%d] попытался проследить за %s[%d]", player_info[playerid][pName], playerid, player_info[to_player][pName], to_player);
    AdmMSG(color_gray, fmt_text);
        return SendClientMessage(playerid, 0x999999FF, "Вы не можете следить за игроками уровня 5 и выше.");
    }

    if (GetPlayerSpectateData(playerid, S_PLAYER) == -1)
    {
        new Float:x, Float:y, Float:z, Float:a, skin = GetPlayerSkin(playerid);
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);

        SetPlayerSpectateData(playerid, S_START_POS_X, x);
        SetPlayerSpectateData(playerid, S_START_POS_Y, y);
        SetPlayerSpectateData(playerid, S_START_POS_Z, z);
        SetPlayerSpectateData(playerid, S_START_ANGLE, a);

        SetPlayerSpectateData(playerid, S_START_INTERIOR, GetPlayerInterior(playerid));
        SetPlayerSpectateData(playerid, S_START_VIRTUAL_WORLD, GetPlayerVirtualWorld(playerid));

        SetSpawnInfo(playerid, 0, skin, x, y, z, a, 0, 0, 0, 0, 0, 0);
    }

    StartSpectate(playerid, to_player);

    new fmt_text[248];
    format(fmt_text, sizeof fmt_text, "Следит скрытно за %s[acc:%d]", player_info[to_player][pName], player_info[to_player][pId]);
    SendLog(playerid, LOG_TYPE_ADMIN_ACTION, fmt_text);

    return 1;
}

CMD:spoff(playerid, params[])
{
    if(GetPlayerAdminEx(playerid) < 1) return 1;

    if(GetPlayerSpectateData(playerid, S_PLAYER) != -1)
    {
        StopSpectate(playerid);
    }

    return 1;
}