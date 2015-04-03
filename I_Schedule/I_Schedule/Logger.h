#pragma once
//@author A0099303A
#include <fstream>
#include <sstream>
#include "DateTime.h";
using namespace std;
namespace logging{
	class Logger
	{
	public:
		Logger();
		~Logger();

	private:
		string _filename = "debug.log";
		string Write(string input);
		
		friend Logger& operator<<(Logger& logger, string input);
	};
	static Logger logfile;
}
