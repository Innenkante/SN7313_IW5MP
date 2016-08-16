#pragma once
class Hook_
{
public:
	void *DetourFunction(BYTE *src, const BYTE *dst, const int len);
private:
};

