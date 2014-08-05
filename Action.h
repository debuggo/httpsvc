#pragma once
#include <string>
using std::string;
class Action
{
public:
	Action(int type = -1, string name = "", string param1 = "", string param2 = "")
		:type_(type), name_(name), param1_(param1), param2_(param2){};
	~Action();
	bool operator == (const Action &other) const 
	{
		return (this->type() == other.type() && this->name() == other.name() && this->param1() == other.param1() 
			&& this->param2() == other.param2());
	}
	Action& operator =(const Action &other)
	{
		this->name_ = other.name();
		this->param1_ = other.param1();
		this->param2_ = other.param2();
		this->type_ = other.type();
		return *this;
	}
	const int type() const { return type_; }
	void type(const int typein){ type_ = typein; }
	const string& name() const { return name_; }
	void name(const string &namein){ name_ = namein; }
	const string& param1() const { return param1_; }
	void param1(const string &param1in){ param1_ = param1in; }
	const string& param2() const { return param2_; }
	void param2(const string &param2in){ param2_ = param2in; }
private:
	int type_;
	string name_;
	string param1_;
	string param2_;
};

