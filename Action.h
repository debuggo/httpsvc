#pragma once
#include <string>
using std::string;
class Action
{
public:

	/**
	 @fn	Action::Action(int type = -1, string param1 = "", string param2 = "", bool isunuseful = false)
	
	 @brief	Ĭ�Ϲ��캯��.
	
	 @author	Debug Go
	 @date	8/6/2014
	
	 @param	type	  	(Optional) ����,Ĭ��Ϊ-1(�����ڵ�����).
	 @param	param1	  	(Optional) ����,Ĭ��Ϊ"".
	 @param	param2	  	(Optional) ���Ӳ���,Ĭ��Ϊ"".
	 @param	isunuseful	(Optional) �Ƿ���Ч,Ĭ��Ϊfalse(��Ч).
	 */

	Action(int type = -1, string param1 = "", string param2 = "", bool isunuseful = false)
		:type_(type), param1_(param1), param2_(param2), isunuseful_(isunuseful){};
	~Action();
	bool operator == (const Action &other) const 
	{
		return (this->type() == other.type() &&  this->param1() == other.param1() 
			&& this->param2() == other.param2() && this->Isunuseful() == other.Isunuseful());
	}
	Action& operator =(const Action &other)
	{
		this->param1_ = other.param1();
		this->param2_ = other.param2();
		this->type_ = other.type();
		this->isunuseful_ = other.Isunuseful();
		return *this;
	}
	//set  get
	const int type() const { return type_; }
	void type(const int typein){ type_ = typein; }
	const string& param1() const { return param1_; }
	void param1(const string &param1in){ param1_ = param1in; }
	const string& param2() const { return param2_; }
	void param2(const string &param2in){ param2_ = param2in; }
	bool Isunuseful() const { return isunuseful_; }
	void Isunuseful(bool val) { isunuseful_ = val; }
	
private:

	/**
	 @brief	����.
	 */

	int type_;

	/**
	 @brief	�Ƿ���Ч.
	 @note true = ��Ч,false = ��Ч.
	 */

	bool isunuseful_;

	/**
	 @brief	����.
	 */

	string param1_;

	/**
	 @brief	���Ӳ���.
	 */

	string param2_;
};

