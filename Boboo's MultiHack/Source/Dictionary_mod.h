#pragma once
class ValuePair
{
public:
	ValuePair(char* EntryName,bool EntryValue);
	bool GetValue();
	void SetValue(bool NewValue);
private:
	char* Name;
	bool Value;
};

//inline ValuePair::ValuePair(char * EntryName, bool EntryValue)
//{
//	Name = EntryName;
//	Value = EntryValue;
//}

