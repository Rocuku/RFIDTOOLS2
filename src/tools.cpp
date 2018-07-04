#include "stdafx.h"
#include "tools.h"

CString cc2cs(const char *cc)
{
	CString str(cc);
	return str;
}

CString str2hex(CString str)
{
	CString hex, tmp;
	for (int i = 0; i < str.GetLength(); i++)
	{
		tmp.Format(_T("%02x "), str[i]);
		hex += tmp;
	}
	return hex;
}

CString hex2str(CString hex)
{
	CString str, tmp;
	char c[2];
	int n;
	BYTE x;
	hex.Remove(' ');
	for (int i = 0; i < hex.GetLength(); i += 2){
		c[0] = hex[i];
		c[1] = hex[i + 1];
		x = strtol(c, NULL, 16);
		tmp.Format(_T("%c"), x);
		str += tmp;
	}
	return str;
}