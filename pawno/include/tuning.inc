#define RPC_STREAM_TEXTURE	0x187
#define RPC_CUSTOM_HANDLING	0x11
#define RPC_CUSTOM_INIT 377
#define PACKET_CUSTOMRPC    			251

stock SetVehTexture(playerid, veh, tex[], tex2[])
{
	new BitStream:bitstream = BS_New();
	BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
	BS_WriteValue(bitstream, PR_UINT32, RPC_STREAM_TEXTURE);

	BS_WriteValue(bitstream, PR_UINT16, veh);	

	BS_WriteValue(bitstream, PR_UINT8, strlen(tex));
	BS_WriteValue(bitstream, PR_STRING, tex);

	BS_WriteValue(bitstream, PR_UINT8, strlen(tex2));
	BS_WriteValue(bitstream, PR_STRING, tex2);

	PR_SendPacket(bitstream, playerid);
	BS_Send(bitstream, playerid);

	BS_Delete(bitstream);
}

stock SetHandlingData(playerid, veh, data[], value)
{
    new BitStream:bitstream = BS_New();
    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
    BS_WriteValue(bitstream, PR_UINT32, RPC_CUSTOM_HANDLING);

    BS_WriteValue(bitstream, PR_UINT16, veh);
    BS_WriteValue(bitstream, PR_UINT8, value);

    // Логируем переданные данные
    printf("Sending %d handling data entries for vehicle %d", value, veh);

    for (new i = 0; i < value; i++)
    {
        new id = data[i * 2];       // Получаем id
        new fvalue = data[i * 2 + 1]; // Получаем fvalue

        printf("Pushing data: id = %d, fvalue = %f", id, fvalue); // Логируем каждое значение

        BS_WriteValue(bitstream, PR_UINT8, id);
        BS_WriteValue(bitstream, PR_FLOAT, fvalue);
    }

    PR_SendPacket(bitstream, playerid);
    BS_Send(bitstream, playerid);

    BS_Delete(bitstream);
}

stock TestInitGame(playerid)
{
    new BitStream:bitstream = BS_New();
    BS_WriteValue(bitstream, PR_UINT8, PACKET_CUSTOMRPC);
    BS_WriteValue(bitstream, PR_UINT32, RPC_CUSTOM_INIT);

    BS_Send(bitstream, playerid);

    BS_Delete(bitstream);
}