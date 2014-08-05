#include "BmIniManagement.h"
//导入boost的property_tree(属性树)库
#include "boost/property_tree/ptree.hpp"
//导入boost的ini_parser(ini语法分析器)库
#include "boost/property_tree/ini_parser.hpp"
//导入boost的lexical_cast
#include "boost/lexical_cast.hpp"
//导入boost的filesystem
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
#include <iostream>

BmIniManagement::~BmIniManagement()
{
}

const std::vector<Action> & BmIniManagement::actions() 
{
	using namespace boost::property_tree;
	actions_.clear();	//清空
	initree_.clear();
	if (!boost::filesystem::exists(path_))	//如果文件为空
	{
		std::ofstream out(path_.c_str());	//创建文件
		out << "[" << section_ << "]" << std::endl;
		out << kActionYype << "0=88" << std::endl;
		out << kParam1 << "0=" << std::endl;
		out << kParam2 << "0=" << std::endl;
		out << kActionName << "0=配置结束" << std::endl;
		out.close();
	}
	try
	{
		read_ini(path_, initree_);
	}
	catch (ini_parser_error err)
	{
		std::cout << err.message() << std::endl;
		//return;
	}
	
	//获取里面节点的信息
	for (int i = 0;; i++)
	{
		//构造节点的名字
		string actionname = section_ + "." + kActionName + boost::lexical_cast<string>(i);
		string actiontype = section_ + "." + kActionYype + boost::lexical_cast<string>(i);
		string actionparam1 =section_ + "." +  kParam1 + boost::lexical_cast<string>(i);
		string actionparam2 =section_ + "." +  kParam2 + boost::lexical_cast<string>(i);
		Action nowaction(initree_.get<int>(actiontype, -1), initree_.get<string>(actionname, ""),
			initree_.get<string>(actionparam1, ""),initree_.get<string>(actionparam2, ""));
		if (nowaction.type() == -1)
		{
			break;
		}
		actions_.push_back(nowaction);
		if (nowaction.type() == 88)
		{
			break;
		}
	}
	return actions_;
}

const std::vector<Action>  BmIniManagement::actions(int type)
{
	std::vector<Action> ret;
	if (actions_.empty())
	{
		actions();
	}

	for (std::vector<Action>::iterator iter = actions_.begin();
		iter != actions_.end(); ++iter)
	{
		if (iter->type() == type)
		{
			ret.push_back(*iter);
		}
	}

	return ret;
}



BmIniManagement::BmIniManagement(string file_path)
{
	size_t pos =  file_path.find('|');
	if (pos != string::npos)
	{
		path_ = file_path.substr(0, pos);
		section_ = file_path.substr(pos + 1, file_path.length());
	}
	else
	{
		path_ = file_path;
	}
}

const std::vector<Action> & BmIniManagement::addaction(const Action &action)
{
	std::vector<Action>::iterator findit = find(actions_.begin(), actions_.end(), action);
	if (findit == actions_.end() && !actions_.empty())	//如果没有找到
	{
		actions_.insert(actions_.end() - 1, action);
	}
	return actions_;
}

const std::vector<Action> & BmIniManagement::delaction(const Action &action)
{
	std::vector<Action>::iterator findit = find(actions_.begin(), actions_.end(), action);
	if (findit != actions_.end())	//如果找到
	{
		actions_.erase(findit);
	}

	return actions_;
}

const std::vector<Action> & BmIniManagement::chageaction(const Action &oldaction, const Action &action)
{
	std::vector<Action>::iterator findit = find(actions_.begin(), actions_.end(), oldaction);
	if (findit != actions_.end())	//如果找到
	{
		//替换的内容是否存在
		std::vector<Action>::iterator it = find(actions_.begin(), actions_.end(), action);
		if (it == actions_.end())	//如果不存在
		{
			*findit = action;			//替换
		}
	}
	return actions_;
}


const std::vector<Action> & BmIniManagement::addactions(std::vector<Action> &add_actions)
{
	for (std::vector<Action>::iterator iter = add_actions.begin();
		iter != add_actions.end(); iter++)
	{
		addaction(*iter);
	}
	return actions_;
}

const std::vector<Action> & BmIniManagement::delactions(const int type)
{
	for (std::vector<Action>::iterator iter = actions_.begin();
		iter != actions_.end(); ++iter)
	{
		if (iter->type() == type)
		{
			iter = actions_.erase(iter);
		}
	}
	return actions_;
}

const std::vector<Action> & BmIniManagement::delactions(const string &name)
{
	for (std::vector<Action>::iterator iter = actions_.begin();
		iter != actions_.end(); ++iter)
	{
		if (iter->name() == name)
		{
			iter = actions_.erase(iter);
		}
	}
	return actions_;
}

const std::vector<Action> & BmIniManagement::delactions(const int type, std::vector<Action> &deleteed_actions)
{
	deleteed_actions.clear();	//清空
	for (std::vector<Action>::iterator iter = actions_.begin();
		iter != actions_.end(); ++iter)
	{
		if (iter->type() == type)
		{
			deleteed_actions.push_back(*iter);
			iter = actions_.erase(iter);
		}
	}
	return actions_;
}

const std::vector<Action> & BmIniManagement::delactions(const string &name, std::vector<Action> &deleteed_actions)
{
	deleteed_actions.clear();
	for (std::vector<Action>::iterator iter = actions_.begin();
		iter != actions_.end(); ++iter)
	{
		if (iter->name() == name)
		{
			deleteed_actions.push_back(*iter);
			iter = actions_.erase(iter);
		}
	}
	return actions_;
}

void BmIniManagement::writetoini()
{
	if (actions_.empty())
	{
		return;
	}
	int i = 0; 
	initree_.erase(initree_.begin(), initree_.end());
	for (std::vector<Action>::iterator iter = actions_.begin();
		iter != actions_.end(); ++iter, ++i)
	{
		//构造节点的名字
		string actionname = section_ + "." + kActionName + boost::lexical_cast<string>(i);
		string actiontype = section_ + "." + kActionYype + boost::lexical_cast<string>(i);
		string actionparam1 =section_ + "." +  kParam1 + boost::lexical_cast<string>(i);
		string actionparam2 =section_ + "." +  kParam2 + boost::lexical_cast<string>(i);
		initree_.put(actiontype, iter->type());
		initree_.put(actionparam1, iter->param1());
		initree_.put(actionparam2, iter->param2());
		initree_.put(actionname, iter->name());
	}
	write_ini(path_, initree_);
}



