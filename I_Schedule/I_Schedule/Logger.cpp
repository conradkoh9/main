#include "Logger.h"

namespace logging{
	Logger::Logger()
	{
	}


	Logger::~Logger()
	{
	}

	string Logger::Write(string input){
		string feedback = "";
		ofstream out;
		DateTime timeinfo;
		out.open(_filename.c_str(), ios::app);
		out << "[" << timeinfo.Today() << "] " << "[" << timeinfo.Now() << "]: " << input << endl;
		out.close();
		return feedback;
	}

	Logger& operator<<(Logger& logger, string input){
		logger.Write(input);
		return logger;
	}
}