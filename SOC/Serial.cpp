#include "Serial.h"

namespace Etc
{
	Serial::Serial(char *portName)			
	{
		errors = 0;
		serial = nullptr;
		connected = false;

		memset(&status, 0, sizeof(COMSTAT));
		memset(buffer, 0, sizeof(char) * maxBufferSize);
	}

	Serial::~Serial()
	{
		Disconnect();
	}

	bool Serial::Recive(std::string *out, unsigned int packetLength)
	{
		DWORD bytesRead;
		unsigned int toRead;

		ClearCommError(serial, &errors, &status);

		if(status.cbInQue > 0)
		{
			toRead = status.cbInQue > packetLength ? packetLength : status.cbInQue;

			ReadFile(serial, buffer, toRead, &bytesRead, NULL);

			if( bytesRead != 0)
			{
				(*out) = buffer;
				PurgeComm(serial, PURGE_TXABORT | PURGE_RXABORT |  PURGE_TXCLEAR | PURGE_RXCLEAR);
				return true;
			}

			memset(buffer, 0, sizeof(char) * maxBufferSize);
		}

		return false;
	}

	bool Serial::Send(char *buffer, unsigned int packetLength)
	{
		DWORD bytesSend;

		if(WriteFile(serial, (void *)buffer, packetLength, &bytesSend, 0) == false)
		{
			ClearCommError(serial, &errors, &status);
			return false;
		}

		return true;
	}

	bool Serial::IsConnected()
	{
		return connected;
	}

	bool Serial::Connect(int portNum)
	{
		char port[10];
		sprintf_s(port, "\\\\.\\COM%d", portNum);

		serial = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if(serial==INVALID_HANDLE_VALUE)
			return false;
		// Handle was not attached.
		else
		{
			DCB dcbSerialParams = {0};

			if (GetCommState(serial, &dcbSerialParams) == false)
				return false; //failed to get current serial parameters!
			else
			{
				dcbSerialParams.BaudRate=CBR_9600;
				dcbSerialParams.ByteSize=8;
				dcbSerialParams.StopBits=ONESTOPBIT;
				dcbSerialParams.Parity=NOPARITY;

				if(SetCommState(serial, &dcbSerialParams) == false)
					return false; //ALERT: Could not set Serial Port parameters
				else
				{
					connected = true;
					Sleep(waitTime);
				}
			}
		}

		return true;
	}
	void Serial::Disconnect()
	{
		if(connected)
		{
			connected = false;
			CloseHandle(serial);
		}
	}

}