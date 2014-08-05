#ifndef BMINIMANAGEMENT_H
#define BMINIMANAGEMENT_H
#include <string>
#include <vector>
#include "Action.h"
//导入boost的property_tree(属性树)库
#include "boost/property_tree/ptree.hpp"
//导入boost的ini_parser(ini语法分析器)库
#include "boost/property_tree/ini_parser.hpp"
using std::string;
class BmIniManagement
{

public:
	
	BmIniManagement() 
		:path_(""), section_(""){};
	BmIniManagement(string file_path);
	BmIniManagement(string file_path, string section) 
		:path_(file_path),section_(section){};
	~BmIniManagement();

	bool operator ==(BmIniManagement &other) const
	{
		return(other.path() == this->path_ && other.path() == this->section_);
	}
	
	const string& path() const { return path_; }
	void path(string &file_path){ path_ = file_path; }
	const string& section() const { return section_; }
	void section(string &section_name){ section_ = section_name; }

	const std::vector<Action> & actions();							//获取所有的actions
	const std::vector<Action>  actions(int type);					//获取指定actions_type

	const std::vector<Action> & addaction(const Action &action);	//添加单个action

	const std::vector<Action> & addactions(std::vector<Action> &add_actions);	//批量添加actions

	const std::vector<Action> & delaction(const Action &action);	//删除单个action

	const std::vector<Action> & delactions(const int type);			//批量删除指定的actions
	const std::vector<Action> & delactions
		(const int type, std::vector<Action> &deleteed_actions);	//批量删除指定的actions,并获取已经删除了的actions
	const std::vector<Action> & delactions
		(const string &name);
	const std::vector<Action> & delactions
		(const string &name, std::vector<Action> &deleteed_actions);

	const std::vector<Action> & chageaction(const Action &oldaction, const Action &action);

	void writetoini();	//将改动写入ini
private:
	string path_;		//ini路径
	string section_;	//ini段名
	std::vector<Action> actions_;	//对应段中的内容
	boost::property_tree::ptree initree_;
	//--- 常量 ---//
	const string kActionYype = "ActionType";
	const string kParam1 = "Param1";
	const string kParam2 = "Param2";
	const string kActionName = "ActionName";

	//--- 方法 ---//
};


#endif // !BMINIMANAGEMENT_H