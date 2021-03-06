/*
Copyright (c) 2011, Gerhard H. Schalk (www.smartcard-magic.net)
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the 
documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <fstream>
using namespace std;

void printHexString(CHAR* sPrefix, LPBYTE baData, DWORD dataLen)
{
	FILE *fp;
	fp=fopen("temp.txt","at");

	DWORD i;

	printf("%s", sPrefix);
	//fprintf(fp, sPrefix);

	for(i = 0; i < dataLen;i++)		
	{
		printf("%02X ",baData[i]);
		fprintf(fp, "%02X",baData[i]);
	}
	
	printf("\n");
	fprintf(fp, "\n");
	fclose(fp);
}

INT cmpByte(LPBYTE array1,LPBYTE array2,INT len)
{
	INT i;

	for(i = 0; i < len; i++)
	{
		if(*array1++ != *array2++)
		{
			return i ? i: -1;
		}
	}
	return 0;
}

void copyByte(LPBYTE des, LPBYTE src, INT len)
{
	INT i;

	for(i = 0; i < len; i++)
	{
		*des++ = *src++;
	}
}





