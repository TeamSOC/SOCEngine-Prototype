#pragma once

#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

namespace Etc
{
	namespace Communication
	{
		class Serial
		{
		private:
			HANDLE serial;
			bool connected;
			COMSTAT status;
			DWORD errors;

		public:
			Serial();
			~Serial();

			bool ConnectArduino(int portNum);

			void Recive(std::string &packet, unsigned int length);
			bool Send(std::string &packet, unsigned int length);
			bool IsConnected();
		};
	}
}