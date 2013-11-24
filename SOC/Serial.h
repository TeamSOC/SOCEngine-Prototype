#pragma once

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

namespace Etc
{
	class Serial
	{
	public:
		static const int maxBufferSize = 256;
		static const int waitTime = 2000;
	private:
		HANDLE serial;
		bool connected;
		COMSTAT status;
		DWORD errors;
		char buffer[maxBufferSize];

	public:
		Serial(char *portName);
		~Serial();

	public:
		bool Connect(int portNum);
		void Disconnect();

		bool Recive(std::string *out, unsigned int packetLength);
		bool Send(char *buffer, unsigned int packetLength);

		bool IsConnected();
	};

}