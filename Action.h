#pragma once
#include "FQ_Std.h"
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
			return L"�ֱ���";
		case 1:
			return L"���ٹػ�";
		case 14:
			return L"VNC����";
		case 6:
			return L"���ô���";
		case 8:
			return L"IP&MAC��";
		case 9:
			return L"�������";
		case 12:
			return L"��������";
		case 15:
			return L"��������";
		case 88:	
			return L"���ý���";
		default:
			return L"";
		}
		
	}
private:

	/**
	 @brief	����.
	 */

	int type_;

	/**
	 @brief	�Ƿ���Ч.
	 @note true = ��Ч,false = ��Ч.
	 */

	bool isoperation_;
	/**
	 @brief	����.
	 */

	CString param1_;

	/**
	 @brief	���Ӳ���.
	 */

	CString param2_;
};

