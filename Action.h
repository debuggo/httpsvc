#pragma once
#include <string>
using std::string;
class Action
{
public:

	/**
	 @fn	Action::Action(int type = -1, string param1 = "", string param2 = "", bool isunuseful = false)
	
	 @brief	默认构造函数.
	
	 @author	Debug Go
	 @date	8/6/2014
	
	 @param	type	  	(Optional) 类型,默认为-1(不存在的类型).
	 @param	param1	  	(Optional) 参数,默认为"".
	 @param	param2	  	(Optional) 附加参数,默认为"".
	 @param	isunuseful	(Optional) 是否有效,默认为false(有效).
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
	 @brief	类型.
	 */

	int type_;

	/**
	 @brief	是否无效.
	 @note true = 无效,false = 有效.
	 */

	bool isunuseful_;

	/**
	 @brief	参数.
	 */

	string param1_;

	/**
	 @brief	附加参数.
	 */

	string param2_;
};

