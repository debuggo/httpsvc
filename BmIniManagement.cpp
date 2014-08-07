#include "BmIniManagement.h"
//����boost��property_tree(������)��
#include "boost/property_tree/ptree.hpp"
//����boost��ini_parser(ini�﷨������)��
#include "boost/property_tree/ini_parser.hpp"
//����boost��lexical_cast
#include "boost/lexical_cast.hpp"
//����boost��filesystem
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
#include <iostream>

BmIniManagement::~BmIniManagement()
{
}

//const std::vector<Action> & BmIniManagement::actions() 
//{
//	using namespace boost::property_tree;
//	actions_.clear();	//���
//	initree_.clear();
//	
//	try
//	{
//		read_ini(path_, initree_);
//	}
//	catch (ini_parser_error err)
//	{
//		std::cout << err.message() << std::endl;
//		//return;
//	}
//	//��ȡ����ڵ����Ϣ
//	for (int i = 0;; i++)
//	{
//		//����ڵ������
//		string actionname = section_ + "." + kActionName + boost::lexical_cast<string>(i);
//		string actiontype = section_ + "." + kActionYype + boost::lexical_cast<string>(i);
//		string actionparam1 =section_ + "." +  kParam1 + boost::lexical_cast<string>(i);
//		string actionparam2 =section_ + "." +  kParam2 + boost::lexical_cast<string>(i);
//		Action nowaction(initree_.get<int>(actiontype, -1), initree_.get<string>(actionname, ""),
//			initree_.get<string>(actionparam1, ""),initree_.get<string>(actionparam2, ""));
//		if (nowaction.type() == -1)
//		{
//			break;
//		}
//		actions_.push_back(nowaction);
//		if (nowaction.type() == 88)
//		{
//			break;
//		}
//	}
//	return actions_;
//}
//
//const std::vector<Action>  BmIniManagement::actions(int type)
//{
//	std::vector<Action> ret;
//	if (actions_.empty())
//	{
//		actions();
//	}
//
//	for (std::vector<Action>::iterator iter = actions_.begin();
//		iter != actions_.end(); ++iter)
//	{
//		if (iter->type() == type)
//		{
//			ret.push_back(*iter);
//		}
//	}
//
//	return ret;
//}
//
//
//
//BmIniManagement::BmIniManagement(string file_path)
//{
//	size_t pos =  file_path.find('|');
//	if (pos != string::npos)
//	{
//		path_ = file_path.substr(0, pos);
//		section_ = file_path.substr(pos + 1, file_path.length());
//	}
//	else
//	{
//		path_ = file_path;
//	}
//}
//
//const std::vector<Action> & BmIniManagement::addaction(const Action &action)
//{
//	std::vector<Action>::iterator findit = find(actions_.begin(), actions_.end(), action);
//	if (findit == actions_.end() && !actions_.empty())	//���û���ҵ�
//	{
//		actions_.insert(actions_.end() - 1, action);
//	}
//	return actions_;
//}
//
//const std::vector<Action> & BmIniManagement::delaction(const Action &action)
//{
//	std::vector<Action>::iterator findit = find(actions_.begin(), actions_.end(), action);
//	if (findit != actions_.end())	//����ҵ�
//	{
//		actions_.erase(findit);
//	}
//
//	return actions_;
//}
//
//const std::vector<Action> & BmIniManagement::chageaction(const Action &oldaction, const Action &action)
//{
//	std::vector<Action>::iterator findit = find(actions_.begin(), actions_.end(), oldaction);
//	if (findit != actions_.end())	//����ҵ�
//	{
//		//�滻�������Ƿ����
//		std::vector<Action>::iterator it = find(actions_.begin(), actions_.end(), action);
//		if (it == actions_.end())	//���������
//		{
//			*findit = action;			//�滻
//		}
//	}
//	return actions_;
//}
//
//
//const std::vector<Action> & BmIniManagement::addactions(std::vector<Action> &add_actions)
//{
//	for (std::vector<Action>::iterator iter = add_actions.begin();
//		iter != add_actions.end(); iter++)
//	{
//		addaction(*iter);
//	}
//	return actions_;
//}
//
//const std::vector<Action> & BmIniManagement::delactions(const int type)
//{
//	for (std::vector<Action>::iterator iter = actions_.begin();
//		iter != actions_.end(); ++iter)
//	{
//		if (iter->type() == type)
//		{
//			iter = actions_.erase(iter);
//		}
//	}
//	return actions_;
//}
//
//const std::vector<Action> & BmIniManagement::delactions(const string &name)
//{
//	for (std::vector<Action>::iterator iter = actions_.begin();
//		iter != actions_.end(); ++iter)
//	{
//		if (iter->name() == name)
//		{
//			iter = actions_.erase(iter);
//		}
//	}
//	return actions_;
//}
//
//const std::vector<Action> & BmIniManagement::delactions(const int type, std::vector<Action> &deleteed_actions)
//{
//	deleteed_actions.clear();	//���
//	for (std::vector<Action>::iterator iter = actions_.begin();
//		iter != actions_.end(); ++iter)
//	{
//		if (iter->type() == type)
//		{
//			deleteed_actions.push_back(*iter);
//			iter = actions_.erase(iter);
//		}
//	}
//	return actions_;
//}
//
//const std::vector<Action> & BmIniManagement::delactions(const string &name, std::vector<Action> &deleteed_actions)
//{
//	deleteed_actions.clear();
//	for (std::vector<Action>::iterator iter = actions_.begin();
//		iter != actions_.end(); ++iter)
//	{
//		if (iter->name() == name)
//		{
//			deleteed_actions.push_back(*iter);
//			iter = actions_.erase(iter);
//		}
//	}
//	return actions_;
//}

//void BmIniManagement::writetoini()
//{
//	if (actions_.empty())
//	{
//		return;
//	}
//	int i = 0; 
//	initree_.erase(initree_.begin(), initree_.end());
//	for (std::vector<Action>::iterator iter = actions_.begin();
//		iter != actions_.end(); ++iter, ++i)
//	{
//		//����ڵ������
//		string actionname = section_ + "." + kActionName + boost::lexical_cast<string>(i);
//		string actiontype = section_ + "." + kActionYype + boost::lexical_cast<string>(i);
//		string actionparam1 =section_ + "." +  kParam1 + boost::lexical_cast<string>(i);
//		string actionparam2 =section_ + "." +  kParam2 + boost::lexical_cast<string>(i);
//		initree_.put(actiontype, iter->type());
//		initree_.put(actionparam1, iter->param1());
//		initree_.put(actionparam2, iter->param2());
//		initree_.put(actionname, iter->name());
//	}
//	write_ini(path_, initree_);
//}
//


//bool BmIniManagement::getdefaultroot(boost::property_tree::ptree &root)
//{
//	/**
//	* ����·���Ƿ�Ϸ�,���ļ��Ƿ����.
//	����ļ�������,�ᴴ���ļ�,������endkey.
//	����ļ��в�����Ĭ�϶�,�����Ĭ�϶���Ϣ��,�ݹ�����������.
//	*/
//	using namespace boost::property_tree;
//	bool ret = false;
//	if (path_ == "")
//	{
//		return ret;
//	}
//	if (!boost::filesystem::exists(path_))	//�ж��ļ��Ƿ����
//	{
//		addendkey(false); //true��ʾʧЧ��
//	}
//	try
//	{
//		read_ini(path_, root);
//		root = root.get_child(kMonitorIniDefaultSection);//��ȡĬ����Ч��
//		ret = true;
//	}
//	catch (ini_parser_error err)
//	{
//		WRITE_LOG(LOG_LEVEL_ERROR, L"%s���ݴ���,%s", path_,err.what());
//		if (root == nullptr)//��ȡ�����Ķ�Ϊ��
//		{
//			addendkey(false);
//			return getdefaultroot();
//		}
//	}
//	return ret;
//}
//
//bool BmIniManagement::getunusefulroot(boost::property_tree::ptree &root)
//{
//	using namespace boost::property_tree;
//	bool ret = false;
//	if (path_ == "")
//	{
//		return ret;
//	}
//	if (!boost::filesystem::exists(path_))//�ļ��������򴴽���д��
//	{
//		addendkey();//Ĭ��Ϊtrue ʧЧ��
//	}
//	try
//	{
//		read_ini(path_, root);
//		root = root.get_child_optional(kMonitorIniUnusefulSection);
//		if (!root)//����β�����
//		{
//			/**
//			* �����εĽ���key��,��������������.
//			*/
//			addendkey(true);
//			return getunusefulroot();
//		}
//		ret = true;
//	}
//	catch (ini_parser_error err)
//	{
//		WRITE_LOG(LOG_LEVEL_ERROR, L"%s���ݴ���:%s", path_,err.what());
//		//TODO:����β�����
//	}
//	return ret;
//}


void BmIniManagement::addendkey(bool isunseful /*= true*/)
{
	std::ofstream out(path_.c_str());	//�����ļ�
	//д����Чsection
	if (isunseful)
	{
		out << "[" << kMonitorIniUnusefulSection<< "]" << std::endl;
	}
	else
	{
		out << "[" << kMonitorIniDefaultSection << "]" << std::endl;
	}
	//д�����key
	out << kActionYype << "0=88" << std::endl;
	out << kParam1 << "0=" << std::endl;
	out << kParam2 << "0=" << std::endl;
	out << kActionName << "0=���ý���" << std::endl;
	out.close();
}



