#ifndef BMINIMANAGEMENT_H
#define BMINIMANAGEMENT_H
#include <string>
#include <vector>
#include "Action.h"
//����boost��property_tree(������)��
#include "boost/property_tree/ptree.hpp"
//����boost��ini_parser(ini�﷨������)��
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

	const std::vector<Action> & actions();							//��ȡ���е�actions
	const std::vector<Action>  actions(int type);					//��ȡָ��actions_type

	const std::vector<Action> & addaction(const Action &action);	//��ӵ���action

	const std::vector<Action> & addactions(std::vector<Action> &add_actions);	//�������actions

	const std::vector<Action> & delaction(const Action &action);	//ɾ������action

	const std::vector<Action> & delactions(const int type);			//����ɾ��ָ����actions
	const std::vector<Action> & delactions
		(const int type, std::vector<Action> &deleteed_actions);	//����ɾ��ָ����actions,����ȡ�Ѿ�ɾ���˵�actions
	const std::vector<Action> & delactions
		(const string &name);
	const std::vector<Action> & delactions
		(const string &name, std::vector<Action> &deleteed_actions);

	const std::vector<Action> & chageaction(const Action &oldaction, const Action &action);

	void writetoini();	//���Ķ�д��ini
private:
	string path_;		//ini·��
	string section_;	//ini����
	std::vector<Action> actions_;	//��Ӧ���е�����
	boost::property_tree::ptree initree_;
	//--- ���� ---//
	const string kActionYype = "ActionType";
	const string kParam1 = "Param1";
	const string kParam2 = "Param2";
	const string kActionName = "ActionName";

	//--- ���� ---//
};


#endif // !BMINIMANAGEMENT_H