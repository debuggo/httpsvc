#pragma once
#include <string>
using std::string;
class BmMonitorIni
{
public:
	BmMonitorIni(const string &path = "./Update/ClientCfg.ini"):path_(path){;}
	~BmMonitorIni(void);
private:
	string path_;
};
