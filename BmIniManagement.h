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

//--- ���� ---//
const string kActionYype = "ActionType";
const string kParam1 = "Param1";
const string kParam2 = "Param2";
const string kActionName = "ActionName";
const string kMonitorIniDefaultSection = "System default";	//Ĭ�ϵĶ�
const string kMonitorIniUnusefulSection = "Unuseful Action";	//��Ч�Ķ�
class BmIniManagement
{
/**
 @enum	GetHowRoots

 @brief	��ȡ��Щ�ڵ���Ϣ.
 */

enum GetHowRoots
{
	/**
	 @brief	��ȡĬ����Ч�νڵ�.
	 */

	kGetDefaultRoot = 0,

	/**
	 @brief	��ȡ��Ч�νڵ�.
	 */

	kGetUnusefulRoot = 1,

	/**
	 @brief	��ȡ���нڵ�.
	 */

	kGetAllRoots = 2
};
public:
	
	BmIniManagement(string file_path = ""):path_(file_path)
	{
		
	}
	~BmIniManagement();

	const string& path() const { return path_; }
	void path(string &file_path){ path_ = file_path; }


	//const std::vector<Action>  actions();							//��ȡ���е�actions
	//const std::vector<Action>  actions(int type);					//��ȡָ��actions_type

	//const std::vector<Action> & addaction(const Action &action);	//��ӵ���action

	//const std::vector<Action> & addactions(std::vector<Action> &add_actions);	//�������actions

	//const std::vector<Action> & delaction(const Action &action);	//ɾ������action

	//const std::vector<Action> & delactions(const int type);			//����ɾ��ָ����actions
	//const std::vector<Action> & delactions
	//	(const int type, std::vector<Action> &deleteed_actions);	//����ɾ��ָ����actions,����ȡ�Ѿ�ɾ���˵�actions
	//const std::vector<Action> & delactions
	//	(const string &name);
	//const std::vector<Action> & delactions
	//	(const string &name, std::vector<Action> &deleteed_actions);

	//const std::vector<Action> & chageaction(const Action &oldaction, const Action &action);

private:

	/**
	 @brief	ini·��.
	 */
	string path_;

	/**
	 @fn	void BmIniManagement::writetoini();
	
	 @brief	���Ķ�д�뵽ini��.
	
	 @date	8/6/2014
	 */

	void writetoini();	//���Ķ�д��ini


	/**
	 @fn	bool BmIniManagement::getdefaultroot();
	
	 @brief	��ȡĬ����Ч����Ϊ�ڵ�.
	
	 @date	8/6/2014
	
	 @return	true if it succeeds, false if it fails.
	 */

	bool getdefaultroot(boost::property_tree::ptree &root);

	/**
	 @fn	bool BmIniManagement::getunusefulroot();
	
	 @brief	��ȡδ��Ч����Ϊ�ڵ�.
	
	 @date	8/6/2014
	
	 @return	true if it succeeds, false if it fails.
	 */

	bool getunusefulroot(boost::property_tree::ptree &root);

	/**
	 @fn	void BmIniManagement::addendkey(bool isunseful = true);
	
	 @brief	��ӽ���key.
	
	 @date	8/6/2014
	
	 @param	isunseful	(Optional) ����Ǹ����еĽ���key.
	 @note true = δ��Ч��,false = ��Ч��.
	 */

	void addendkey(bool isunseful = true);
};


#endif // !BMINIMANAGEMENT_H