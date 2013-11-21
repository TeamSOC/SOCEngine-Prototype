#include "Serial.h"

namespace Etc
{
	namespace Communication
	{
		Serial::Serial()
		{
			serial = nullptr;
			connected = false;
		}

		Serial::~Serial()
		{
			if(this->connected)
				CloseHandle(this->serial);
		}

		bool Serial::ConnectArduino(int portNum)
		{
			char port[10];
			sprintf(port, "\\\\.\\COM%d", portNum);

			serial = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

			if(this->serial==INVALID_HANDLE_VALUE)
				return false; //포트 번호 체크 다시해봐
			DCB dcbSerialParams = {0};

			if (GetCommState(this->serial, &dcbSerialParams) == false)
				return false; //현재 시리얼의 파라메터 얻어올 수 없듬

			dcbSerialParams.BaudRate=CBR_9600;
			dcbSerialParams.ByteSize=8;
			dcbSerialParams.StopBits=ONESTOPBIT;
			dcbSerialParams.Parity=NOPARITY;

			if(SetCommState(serial, &dcbSerialParams) == false)
				return false; // 포트 파라메터 세팅 안됨

			this->connected = true;
			Sleep(ARDUINO_WAIT_TIME);
		}

		void Serial::Recive(std::string &buffer, unsigned int length)
		{
			DWORD bytesRead;
			unsigned int toRead;
			char incomingData[256] = "";

			length -= 1;

			ClearCommError(serial, &errors, &status);

			if(status.cbInQue>0)
			{
				toRead = status.cbInQue > length ? length : status.cbInQue;

				while(1)
				{
					if( (ReadFile(serial, incomingData, toRead, &bytesRead, NULL) && bytesRead != 0 ) == false)
						continue;

					int len = strlen(incomingData);
					for(int i=0; i<len; ++i)
					{
						if(incomingData[i] != '\n' && incomingData[i] != '\r')
						{
							buffer += incomingData[i];

							if(buffer.length() > length)
								return;
						}
					}
				}

			}
		}


		bool Serial::Send(std::string &packet, unsigned int nbChar)
		{
			DWORD bytesSend;

			if(!WriteFile(serial, (void *)packet.c_str(), nbChar, &bytesSend, 0))
			{
				ClearCommError(serial, &errors, &status);
				return false;
			}
			else return true;
		}

		bool Serial::IsConnected()
		{
			return connected;
		}

	}
}