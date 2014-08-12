#pragma once
#include "FQ_Std.h"
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

	Action(int type = -1, CString param1 = L"", CString param2 = L"", bool isoperation = false)
		:type_(type), param1_(param1), param2_(param2), isoperation_(isoperation){};
	~Action();
	bool operator == (const Action &other) const 
	{
		return (this->type() == other.type() &&  this->param1() == other.param1() 
			&& this->param2() == other.param2() /*&& this->Isoperation() == other.Isoperation()*/);
	}
	Action& operator =(const Action &other)
	{
		this->param1_ = other.param1();
		this->param2_ = other.param2();
		this->type_ = other.type();
		this->isoperation_ = other.Isoperation();
		return *this;
	}
	//set  get
	const int type() const { return type_; }
	void type(const int typein){ type_ = typein; }
	const CString& param1() const { return param1_; }
	void param1(const CString &param1in){ param1_ = param1in; }
	const CString& param2() const { return param2_; }
	void param2(const CString &param2in){ param2_ = param2in; }
	bool Isoperation() const { return isoperation_; }
	void Isoperation(bool val) { isoperation_ = val; }
	inline const CString name() const 
	{
		switch(type_)
		{
		case 0:
			return L"分辨率";
		case 1:
			return L"快速关机";
		case 14:
			return L"VNC控制";
		case 6:
			return L"禁用窗口";
		case 8:
			return L"IP&MAC绑定";
		case 9:
			return L"网络控制";
		case 12:
			return L"禁用网络";
		case 15:
			return L"保护程序";
		case 88:	
			return L"配置结束";
		default:
			return L"";
		}
		
	}
private:

	/**
	 @brief	类型.
	 */

	int type_;

	/**
	 @brief	是否有效.
	 @note true = 有效,false = 无效.
	 */

	bool isoperation_;
	/**
	 @brief	参数.
	 */

	CString param1_;

	/**
	 @brief	附加参数.
	 */

	CString param2_;
};

