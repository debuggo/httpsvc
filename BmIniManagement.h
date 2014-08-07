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

//--- 常量 ---//
const string kActionYype = "ActionType";
const string kParam1 = "Param1";
const string kParam2 = "Param2";
const string kActionName = "ActionName";
const string kMonitorIniDefaultSection = "System default";	//默认的段
const string kMonitorIniUnusefulSection = "Unuseful Action";	//无效的段
class BmIniManagement
{
/**
 @enum	GetHowRoots

 @brief	获取那些节点信息.
 */

enum GetHowRoots
{
	/**
	 @brief	获取默认生效段节点.
	 */

	kGetDefaultRoot = 0,

	/**
	 @brief	获取无效段节点.
	 */

	kGetUnusefulRoot = 1,

	/**
	 @brief	获取所有节点.
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


	//const std::vector<Action>  actions();							//获取所有的actions
	//const std::vector<Action>  actions(int type);					//获取指定actions_type

	//const std::vector<Action> & addaction(const Action &action);	//添加单个action

	//const std::vector<Action> & addactions(std::vector<Action> &add_actions);	//批量添加actions

	//const std::vector<Action> & delaction(const Action &action);	//删除单个action

	//const std::vector<Action> & delactions(const int type);			//批量删除指定的actions
	//const std::vector<Action> & delactions
	//	(const int type, std::vector<Action> &deleteed_actions);	//批量删除指定的actions,并获取已经删除了的actions
	//const std::vector<Action> & delactions
	//	(const string &name);
	//const std::vector<Action> & delactions
	//	(const string &name, std::vector<Action> &deleteed_actions);

	//const std::vector<Action> & chageaction(const Action &oldaction, const Action &action);

private:

	/**
	 @brief	ini路径.
	 */
	string path_;

	/**
	 @fn	void BmIniManagement::writetoini();
	
	 @brief	将改动写入到ini中.
	
	 @date	8/6/2014
	 */

	void writetoini();	//将改动写入ini


	/**
	 @fn	bool BmIniManagement::getdefaultroot();
	
	 @brief	获取默认生效的行为节点.
	
	 @date	8/6/2014
	
	 @return	true if it succeeds, false if it fails.
	 */

	bool getdefaultroot(boost::property_tree::ptree &root);

	/**
	 @fn	bool BmIniManagement::getunusefulroot();
	
	 @brief	获取未生效的行为节点.
	
	 @date	8/6/2014
	
	 @return	true if it succeeds, false if it fails.
	 */

	bool getunusefulroot(boost::property_tree::ptree &root);

	/**
	 @fn	void BmIniManagement::addendkey(bool isunseful = true);
	
	 @brief	添加结束key.
	
	 @date	8/6/2014
	
	 @param	isunseful	(Optional) 添加那个段中的结束key.
	 @note true = 未生效段,false = 生效段.
	 */

	void addendkey(bool isunseful = true);
};


#endif // !BMINIMANAGEMENT_H