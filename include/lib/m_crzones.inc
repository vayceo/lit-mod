/*

	About: Zones names include v1.0
	Author: Noname

*/

#if defined _m_crzones_included_
	#endinput
#endif
#define _m_crzones_included_

/*
	Define const
*/

#if !defined MAX_ZONES_NAME
	#define MAX_ZONES_NAME 26
#endif

/*
	Enums
*/

enum e_z_CRZones {
    z_Name[MAX_ZONES_NAME char],
	Float:z_Min_x, Float:z_Min_Y, Float:z_Min_Z,
	Float:z_Max_X, Float:z_Max_Y, Float:z_Max_Z
};

/*
	Vars
*/

static z_CRCitys[15][e_z_CRZones] = {
	{!"Гарель",						  2167.0, -339.0, -242.90, 2700.0, 0.0, 900.0},
	{!"Новый Арзамас",				  -1541.0, -601.0, -242.90, 1821.0, 1.0, 900.00},
	{!"Эдово",						  -2691.0, 2536.0, -242.90, -2335.0, 2977.0, 900.00},
	{!"Аэропорт Лыткарино",			  -2588.0, 446.0, -242.90, -2354.0, 510.0, 900.00},
	{!"Нижегородск",				  -2905.0, 1273.0, -242.90, -2228.0, 2121.0, 900.00},
	{!"Гоночный трек",				  -2068.0, 1253.0, -242.90, -1374.0, 2060.0, 900.00},
	{!"Завод",						  -1126.0, 2159.0, -242.90, -1021.0, 2255.0, 900.00},
	{!"Арзамас",					  -434.0, 1.0, -242.90, 917.0, 1097.0, 900.00},
	{!"Арзамас",					  -198.0, 1097.0, -242.90, 631.0, 2029.0, 900.00},
	{!"Арзамас",					  -685.0, 899.0, -242.90, -434.0, 1032.0, 900.00},
	{!"Батырево",					  1715.0, 1837.0, -242.90, 2005.0, 2609.0, 900.00},
	{!"Батырево",					  1921.0, 1732.0, -242.90, 2015.0, 1837.0, 900.00},
	{!"Аэропорт Батырево",			  1098.0, 1516.0, -242.90, 1921.0, 1837.0, 900.00},
	{!"Роговичи",					  1741.0, 1311.0, -242.90, 2362.0, 1516.0, 900.00},
	{!"Лыткарино",					  -2682.0, -268.0, -242.90, -1964.0, 356.0, 900.00}
};

static z_CRAreas[1][e_z_CRZones] = {
	{!"-",					  0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
};

/*
	GetCityName
*/

stock GetCityName(Float:x, Float:y, name[], size = sizeof(name))
{
	for (new i = sizeof(z_CRCitys) - 1; i != -1; i--) {
		if (((x >= z_CRCitys[i][z_Min_x]) && (x <= z_CRCitys[i][z_Max_X])) && ((y >= z_CRCitys[i][z_Min_Y]) && (y <= z_CRCitys[i][z_Max_Y]))) {
			return strunpack(name, z_CRCitys[i][z_Name], size);
		}
	}
	return -1;
}

/*
	GetAreaName
*/

stock GetAreaName(Float:x, Float:y, name[], size = sizeof(name))
{
	for (new i = sizeof(z_CRAreas) - 1; i != -1; i--) {
		if (((x >= z_CRAreas[i][z_Min_x]) && (x <= z_CRAreas[i][z_Max_X])) && ((y >= z_CRAreas[i][z_Min_Y]) && (y <= z_CRAreas[i][z_Max_Y]))) {
			return strunpack(name, z_CRAreas[i][z_Name], size);
		}
	}
	return -1;
}