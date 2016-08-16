#include "stdafx.h"
#include "Dictionary_mod.h"

ValuePair::ValuePair(char * EntryName, bool EntryValue)
{
	Name = EntryName;
	Value = EntryValue;
}

bool ValuePair::GetValue()
{
	return Value;
}

void ValuePair::SetValue(bool NewValue)
{
	Value = NewValue;
}
