#ifndef TEXT_H
#define TEXT_H
#include "include.h"

void t();
void info(string, string, short = 1);
void warn(string, string, short = 1);
void err(string, string, short = 1);
void debug(string, short = 1);
bool readLineXFromIni(int, string&, string&);

void co(int ForgC=15, int BackC=0)
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
void t()
{
	time_t timep;
	struct tm* p;
	time(&timep);
	p = localtime(&timep);
	printf("%02d:%02d:%02d ", p->tm_hour, p->tm_min, p->tm_sec);
	//printf("%d/%d/%d %02d:%02d:%02d ", 1900 + p->tm_year, 1+ p->tm_mon, p->tm_mday,p->tm_hour, p->tm_min, p->tm_sec);
	return;
}
string t2()
{
	string re;
	time_t timep;
	struct tm* p;
	time(&timep); 
	p = localtime(&timep);
	re = to_string(1900 + p->tm_year) + "_" + to_string(1 + p->tm_mon) + "_" + to_string(p->tm_mday) + "_" + to_string(p->tm_hour) + "_" + to_string(p->tm_min) + "_" + to_string(p->tm_sec);
	//printf("%d/%d/%d %02d:%02d:%02d ", 1900 + p->tm_year, 1+ p->tm_mon, p->tm_mday,p->tm_hour, p->tm_min, p->tm_sec);
	return re;
}
void info(string who, string text, short l)
{
	t();
	cout << "<";
	co(9);
	cout << "INFO";
	co(8);
	cout << ":" << who;
	co();
	cout << "> " << text;
	if (l)cout << endl;
	fout << "<INFO:" << who << ">" << text;
	if (l)fout << endl;
}
void debug(string text, short l)
{
	t();
	cout << "<";
	co(10);
	cout << "DEBUG";
	co();
	cout << "> " << text;
	if (l)cout << endl;
	fout << "<DEBUG>" << text;
	if (l)fout << endl;
}
void warn(string who, string text, short l)
{
	t();
	cout << "<";
	co(14);
	cout << "WARN";
	co(8);
	cout << ":" << who;
	co();
	cout << "> " << text;
	if (l)cout << endl;
	fout << "<WARN:" << who << ">" << text;
	if (l)fout << endl;
}
void err(string who, string text, short l)
{
	t();
	cerr << "<";
	co(12);
	cerr << "ERROR";
	co(8);
	cerr << ":" << who;
	co();
	cerr << "> " << text;
	if (l)cout << endl;
	fout << "<ERROR:" << who << ">" << text;
	if (l)fout << endl;
}
int my()
{
	return 0;
}
bool readLineXFromIni(int x, string& key, string& value) {
	string line;
	int currentLine = 1; 

	if (currentLine == x) {
		std::size_t pos = line.find('=');
		if (pos != std::string::npos) {
			key = line.substr(0, pos);
			value = line.substr(pos + 1);
			return true;
		}
	}
	return false;
}



void init()
{
	co();
	getcwd(str, sizeof(str));
	string logto = str;
	logto += "\\data";
	string loga = logto + "\\log\\" + t2() + ".log";
	debug(loga);

	//info("server", "starting server...");
	iout.open("config.ini", ios_base::out | ios_base::app);
	if (!iout.is_open())
	{
		warn("stringio", "Failed to open configuration file");
		ifstream iin("config.ini");
		if (!iin.is_open()) eout;
		iout.open("config.ini", ios_base::out | ios_base::app);
		if (!iout.is_open())
		{
			err("stringio", "Failed to open configuration file");
		}
	}
	else {

	}

	fout.open(loga.c_str(), ios_base::out | ios_base::app);
	if (!fout.is_open())
	{
		//warn("stringio","Failed to open log file");
		if (!CreateDirectory(logto.c_str(), NULL))
		{
			err("fileio", "Failed to open data folder");
			eout;
		}
		logto += "\\log";
		if (!CreateDirectory(logto.c_str(), NULL))
		{
			err("fileio", "Failed to open log folder");
			eout;
		}
		ifstream fin(loga.c_str());
		if (!fin.is_open()) err("stringio", "Failed to open configuration file");
		iout.open(loga.c_str(), ios_base::out | ios_base::app);
		if (!fout.is_open())
		{
			err("stringio", "Failed to open log file");
		}
	}
	if (BUILD_VISION==DEBUG)
	{
		debug("you are into the DEBUG mode!!!");
	}
	if (BUILD_VISION == BUILD)
	{
		debug("you are into the BUILD mode!!!");
	}
}
#endif