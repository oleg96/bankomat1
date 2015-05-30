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
#include <fstream>
#include <clocale>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include "pcsc.h"
#include "util.h"
#include "clessCardType.h"
#include <string>
using namespace std;

struct cassets
{
	int cost;
	int count;
};
int calc(cassets *m, cassets *mtemp, int count, int sum, int newsum, int index, bool &found, bool correct, int n, bool perep)
{
	while (1)
	{
		if (found == true) break;
		if (correct == false) break;
		if (perep == true)
			{
				index++;
				n = 0;
//				correct = false;
				perep=false;
			}
		for (int i = index; i < count; i++)
		{
			if (found == true) break;
			if (correct == false) break;
			if (newsum > m[i].cost && newsum - m[i].cost != 0)
			{
				if (newsum > m[i].cost && newsum - m[i].cost >= m[count - 1].cost)
				{
					if (mtemp[i].count<=0) 
					{
						perep = true;
						//mtemp[i].count=m[i].count;
						calc(m, mtemp, count, sum, newsum, index, found, correct, n, perep);
					}
					newsum -= m[i].cost;
					mtemp[i].count--;
					//n++;
					//cout << n << endl;
					if (mtemp[i].count<=0) 
					{
						perep = true;
						//mtemp[i].count=m[i].count;
					}
					//cout << "+" << m[i].cost << endl;
					//cout << newsum << "*" << i << endl;
					calc(m, mtemp, count, sum, newsum, index, found, correct, n, perep);
				}
				else
				{
					if (i < count - 1)
					{
						index++;
						n = 0;
					}
				}
			}
			else
			{
				if (newsum - m[i].cost == 0)
				{
//					n++;
					//cout << n << endl;
					if (mtemp[i].count<=0) 
					{
						perep = true;
						found = false;
						correct = false;
						break;
					}
					newsum -= m[i].cost;
					mtemp[i].count--;
					//cout << "+" << m[i].cost << endl;
					//cout << newsum << "*" << i << endl;
					found = true;
					ofstream nomin("tempnominals.txt");
					for (int k=0; k<count; k++)
					{
						nomin << mtemp[k].count << " ";
					}
					nomin.close();
					//cout << found << "!" << endl;
				}
			}
			if (i == count - 1 && found == false)
			{
				//cout << "Некорректная сумма" << endl;
				correct = false;
				break;
			}
			//Sleep(1000);
		}
	}
	if (correct == false)
	{
		return 2;
	}
	if (correct == true) return 1;
}
void outmoney(cassets *m, cassets *mtemp, int count, int sum, int newsum, int index, bool &found, bool correct, int n, bool perep)
{
/*	while (1)
	{
		if (found == true) break;
		if (correct == false) break;
		if (perep == true)
			{
				index++;
				n = 0;
//				correct = false;
			}
		for (int i = index; i < count; i++)
		{
			if (found == true) break;
			if (correct == false) break;
			if (newsum > m[i].cost && newsum - m[i].cost != 0)
			{
				if (newsum > m[i].cost && newsum - m[i].cost >= m[count - 1].cost)
				{
					newsum -= m[i].cost;
					mtemp[i].count--;
//					n++;
					//cout << n << endl;
					if (n > m[i].count) perep = true;
					m[i].count--;
					setlocale(LC_ALL, ".866");
					for (int j = 0; j < 80; j++)
					{
						cout << (char)196;
					}
					cout << (char)176 << " " << m[i].cost << endl;
					//cout << newsum << "*" << i << endl;
					outmoney(m, mtemp, count, sum, newsum, index, found, correct, n, perep);
				}
				else
				{
					if (i < count - 1)
					{
						index++;
						n = 0;
					}
				}
			}
			else
			{
				if (newsum - m[i].cost == 0)
				{
					newsum -= m[i].cost;
					n++;
					//cout << n << endl;
					if (n > m[i].count) perep = true;
					m[i].count--;
					setlocale(LC_ALL, ".866");
					for (int j = 0; j < 80; j++)
					{
						cout << (char)196;
					}
					cout << (char)176 << " " << m[i].cost << endl;
					//cout << newsum << "*" << i << endl;
					found = true;
					//cout << found << "!" << endl;
				}
			}
			if (i == count - 1 && found == false)
			{
				//cout << "Некорректная сумма" << endl;
				correct = false;
				break;
			}
			//Sleep(1000);
		}
	}
	*/
	ifstream nomin("tempnominals.txt");
	for (int k=0; k<count; k++)
	{
		nomin >> mtemp[k].count;
	}
	nomin.close();
	cout << endl;
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	setlocale(LC_ALL, ".866");
	SetConsoleTextAttribute(hCon, 9);
	for(int i=0;i<80;i++)
	{
		cout << (char)177;
	}
	SetConsoleTextAttribute(hCon, 7);
	int temp=0;
	for (int k=0; k<count; k++)
	{
		if (m[k].count-mtemp[k].count>0) 
		{
			temp=m[k].count-mtemp[k].count;
			for(int i=0; i<temp; i++)
			{
				//cout << temp << endl;
				for (int j = 0; j < 80; j++)
				{
					cout << (char)196;
				}
				cout << (char)176 << " " << m[k].cost << endl;
				m[k].count--;
			}
		}
	}
}
struct data
{
	string ATR;
	string capdu;
	string rapdu;
};
struct cardsData
{
	string ATR;
	string capdu;
	string rapdu;
	int PIN;
	int counter;
	int moneycount;
};
int cardPIN()
{
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hCon, &info); // Получаем информацию о позиции курсора
    COORD cPos = {info.dwCursorPosition.X, info.dwCursorPosition.Y}; // запоминаем ее
	int Y = 1;
	data *dt = new data[1];
	string c;
	int count=0;
	ifstream temp("temp.txt");
	temp >> dt[0].ATR;
	temp >> dt[0].capdu;
	temp >> dt[0].rapdu;
	temp.close();
	ifstream cards1("cards.txt");
	while(cards1 >> c)
	{
		count++;
	}
	cards1.close();
	count/=6;
	cardsData *dtc = new cardsData[count];
	ifstream cards2("cards.txt");
	for(int i=0; i<count; i++)
	{
		cards2 >> dtc[i].ATR;
		cards2 >> dtc[i].capdu;
		cards2 >> dtc[i].rapdu;
		cards2 >> dtc[i].PIN;
		cards2 >> dtc[i].counter;
		cards2 >> dtc[i].moneycount;
	}
	int i0=-1;
	for(int i=0; i<count; i++)
	{
		if(dt[0].ATR==dtc[i].ATR && dt[0].capdu==dtc[i].capdu && dt[0].rapdu==dtc[i].rapdu) i0=i;
	}
	int PIN=0;
	if(i0!=-1)
	{
		if(dtc[i0].counter==3) 
		{
			/*setlocale(LC_ALL, ".866");
			for (int j = 0; j < 80; j++)
			{
				cout << (char)196;
			}*/
			setlocale(LC_ALL, "Russian");
			SetConsoleTextAttribute(hCon, 192);
			cout << "Карточка заблокирована (превышено количество попыток ввода PIN кода)            ";
			SetConsoleTextAttribute(hCon, 7);
			ofstream temp0("temp.txt");
			temp0.close();
			return 2;
		}
		setlocale(LC_ALL, ".866");
		cout << (char)201;
	for (int i = 0; i < 78; i++)
	{
		cout << (char)205;
	}
	cout << (char)187;
	cout << (char)186;
	setlocale(LC_ALL, "Russian");
		cout << "Введите PIN код (" << 3-dtc[i0].counter << ")";
		setlocale(LC_ALL, ".866");
		cPos.Y++;
		cPos.X = (80 - strlen(" "));
		SetConsoleCursorPosition(hCon, cPos);
		cout << (char)186;
		cout << (char)186;
		cPos.X = (80 - strlen(" "));
		cPos.Y++;
		SetConsoleCursorPosition(hCon, cPos);
		cout << (char)186;
		cout << (char)211;
		for(int i=0;i<78;i++)
		{
			cout << char(196);
		}
		cout << char(189);
		cPos.X = (1);
		SetConsoleCursorPosition(hCon, cPos);
		string PINstr;
		getline(cin, PINstr);
		if(PINstr.empty())
		while((PINstr.empty()))
		{
			cPos.X = (1);
			SetConsoleCursorPosition(hCon, cPos);
			getline(cin, PINstr);
		}
		cPos.Y++;
		cPos.X=0;
		SetConsoleCursorPosition(hCon, cPos);
		cout << char(199);
		cPos.X = (80 - strlen(" "));
		SetConsoleCursorPosition(hCon, cPos);
		cout << char(182);
		cPos.Y++;
		cPos.X=0;
		SetConsoleCursorPosition(hCon, cPos);
		PIN=atoi(PINstr.c_str());
		setlocale(LC_ALL, "Russian");
		if(PIN==dtc[i0].PIN) 
		{
			ofstream temp("cardsum.txt");
			temp << dtc[i0].moneycount << " " << count;
			return 1;
		}
		else
		{
			/*setlocale(LC_ALL, ".866");
			for (int j = 0; j < 80; j++)
			{
				cout << (char)196;
			}*/
			cPos.Y--;
			cPos.X=0;
			SetConsoleCursorPosition(hCon, cPos);
			setlocale(LC_ALL, ".866");
			cout << char(211);
			cPos.X = (80 - strlen(" "));
			SetConsoleCursorPosition(hCon, cPos);
			cout << char(189);
			setlocale(LC_ALL, "Russian");
			SetConsoleTextAttribute(hCon, 192);
			cout << "Неверный PIN код                                                                ";
			SetConsoleTextAttribute(hCon, 7);
			dtc[i0].counter++;
			ofstream cardsErr("cards.txt");
			for(int i=0; i<count; i++)
			{
				cardsErr << dtc[i].ATR << endl;
				cardsErr << dtc[i].capdu << endl;
				cardsErr << dtc[i].rapdu << endl;
				cardsErr << dtc[i].PIN << endl;
				cardsErr << dtc[i].counter << endl;
				cardsErr << dtc[i].moneycount << endl;
			}
			ofstream temp0("temp.txt");
			temp0.close();
			return 3;
		}
	}
	else 
	{
		//setlocale(LC_ALL, ".866");
		//for (int j = 0; j < 80; j++)
		//{
		//	cout << (char)196;
		//}
		setlocale(LC_ALL, "Russian");
		SetConsoleTextAttribute(hCon, 192);
		cout << "Карточка не найдена                                                             ";
		SetConsoleTextAttribute(hCon, 7);
		return 4;
	}
}

int main(int argc, char* argv[])
{
	while (1)
    {
    // Get Data: CLA = 0xFF, INS = 0xCA, P1 = 0x00, P2 = 0x00, Le = 0x00
    BYTE baCmdApduGetData[] = { 0xFF, 0xCA, 0x00, 0x00, 0x00};

    BYTE baResponseApdu[300];	
	DWORD lResponseApduLen = 0;

    BYTE atr[40];
	INT	 atrLength;
	LONG lRetValue;

	HANDLE hCon;
	COORD cPos;
	int Y = 1;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);

	system("cls");
	setlocale(LC_ALL, ".866");
	cPos.Y = Y;
	cPos.X = (80 - strlen("БАНКОМАТ\n\n"));
	SetConsoleCursorPosition(hCon, cPos);
	cout << (char)176;
	setlocale(LC_ALL, "Russian");
	printf("БАНКОМАТ\n\n");
	
	lRetValue = PCSC_Connect(NULL );
    PCSC_EXIT_ON_ERROR(lRetValue);
    
    lRetValue = PCSC_WaitForCardPresent();
    PCSC_EXIT_ON_ERROR(lRetValue);

    lRetValue = PCSC_ActivateCard();
    PCSC_EXIT_ON_ERROR(lRetValue);
    
    lRetValue = PCSC_GetAtrString(atr, &atrLength);
    PCSC_EXIT_ON_ERROR(lRetValue);

    // Send pseudo APDU to retrieve the card serical number (UID)
    PCSC_Exchange(baCmdApduGetData,(DWORD)sizeof(baCmdApduGetData),baResponseApdu, &lResponseApduLen);
	PCSC_EXIT_ON_ERROR(lRetValue);
    
    // Verify if status word SW1SW2 is equal 0x9000.
    if( baResponseApdu[lResponseApduLen - 2] == 0x90 &&
        baResponseApdu[lResponseApduLen - 1] == 0x00)
    {
        // Contactless card detected.
	    // Retrieve the card serical number (UID) form the response APDU.
	    printHexString("Card Serial Number (UID): 0x", baResponseApdu, lResponseApduLen - 2);

	    if( getClessCardType(atr) == Mifare1K)
	    {
            printf("Card Type: MIFARE Classic 1k");
	    }
	    else if( getClessCardType(atr) == Mifare4K)
	    {
		    printf("Card Type: MIFARE Classic 4k");
	    }
	    else if( getClessCardType(atr) == MifareUL)
	    {
		    printf("Card Type: MIFARE Ultralight");
	    }
    }

    //lRetValue = PCSC_WaitForCardRemoval();

    PCSC_Disconnect();
    
    printf("\n");
	Sleep(1000);
	system("cls");
	setlocale(LC_ALL, ".866");
	int sum = 0, t = 0, count = 0;
	ifstream f("money.txt");
	while (f >> t) count++;
	f.close();
	count /= 2;
	cassets *m = new cassets[count];
	cassets *mtemp = new cassets[count];
	ifstream f1("money.txt");
	for (int i = 0; i < count; i++)
	{
		f1 >> m[i].cost;
		f1 >> m[i].count;
	}
	f1.close();
	int tempcost = 0, tempcount = 0;
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = i + 1; j < count; j++)
		{
			if (m[i].cost < m[j].cost)
			{
				tempcost = m[i].cost;
				tempcount = m[i].count;
				m[i].cost = m[j].cost;
				m[i].count = m[j].count;
				m[j].cost = tempcost;
				m[j].count = tempcount;
			}
		}
	}
	for (int i = 0; i < count; i++)
	{
		mtemp[i].cost = m[i].cost;
		mtemp[i].count = m[i].count;
	}
	cout << (char)201;
	for (int i = 0; i < 78; i++)
	{
		cout << (char)205;
	}
	cout << (char)187;
	cout << (char)186;
	setlocale(LC_ALL, "Russian");
	   /*for(int i=0; i<300; i++) {
	SetConsoleTextAttribute(hCon, i);
	cout << " X ";
 
	SetConsoleTextAttribute(hCon, 15);
	cout << " - SetConsoleTextAttribute(h, " << i << ")\n";
   }
   */
	SetConsoleTextAttribute(hCon, 23);
	cout << " Номиналы ";
	SetConsoleTextAttribute(hCon, 7);
	setlocale(LC_ALL, ".866");
	cout <<(char)179;
	setlocale(LC_ALL, "Russian");
	SetConsoleTextAttribute(hCon, 23);
	cout << " количество ";
	setlocale(LC_ALL, ".866");
	SetConsoleTextAttribute(hCon, 7);
	cout << (char)179;
	cout.width(46);
	setlocale(LC_ALL, ".866");
	cout << (char)176;
	setlocale(LC_ALL, "Russian");
	cout << "БАНКОМАТ";
	cPos.Y = Y;
	cPos.X = (80-strlen(" "));
	SetConsoleCursorPosition(hCon, cPos);
	setlocale(LC_ALL, ".866");
	cout << (char)186;
	for (int i = 0; i < count; i++)
	{
		cout << (char)186; SetConsoleTextAttribute(hCon, 10); cout.width(10); cout << m[i].cost;
		SetConsoleTextAttribute(hCon, 7);
		cout << (char)179;
		SetConsoleTextAttribute(hCon, 14); cout.width(12); cout << m[i].count;
		SetConsoleTextAttribute(hCon, 7);
		cout << (char)179;
		Y += 1;
		cPos.Y = Y;
		cPos.X = (80 - strlen(" "));
		SetConsoleCursorPosition(hCon, cPos);
		cout << (char)186;
	}
	int dostsum = 0;
	for (int i = 0; i < count; i++)
	{
		dostsum+=m[i].cost*m[i].count;
	}
	if (dostsum==0) 
    {
		setlocale(LC_ALL, ".866");
		for (int j = 0; j < 80; j++)
		{
			cout << (char)196;
		}
		setlocale(LC_ALL, "Russian");
		SetConsoleTextAttribute(hCon, 12);
        cout << "В банкомате нет средств" << endl;
		SetConsoleTextAttribute(hCon, 7);
        break;
    }
	cout << (char)199;
	for (int i = 0; i < 78; i++)
	{
		cout << (char)196;
	}
	cout << (char)182;
	cout << (char)186;
	setlocale(LC_ALL, "Russian");
	SetConsoleTextAttribute(hCon, 11);
	cout << "Доступная сумма:" << endl;
	SetConsoleTextAttribute(hCon, 7);
	setlocale(LC_ALL, ".866");
	Y += 2;
	cPos.Y = Y;
	cPos.X = (80 - strlen(" "));
	SetConsoleCursorPosition(hCon, cPos);
	cout << (char)186;
	cout << (char)186 << dostsum;
	setlocale(LC_ALL, ".866");
	Y += 1;
	cPos.Y = Y;
	cPos.X = (80 - strlen(" "));
	SetConsoleCursorPosition(hCon, cPos);
	cout << (char)186;
	cout << (char)200;
	for (int i = 0; i < 78; i++)
	{
		cout << (char)205;
	}
	cout << (char)188;
	setlocale(LC_ALL, "Russian");
	int tempcard=0;
	tempcard=cardPIN();
	if(tempcard==1)
	{
	int cardsum=0, countcards=0;
	ifstream tempsum("cardsum.txt");
	tempsum >> cardsum;
	tempsum >> countcards;
	tempsum.close();
	ofstream tempsum0("cardsum.txt");
	tempsum0.close();
	setlocale(LC_ALL, ".866");
	cout << (char)186;
	setlocale(LC_ALL, "Russian");
	cout << "Сумма, доступная на карточке: ";
	setlocale(LC_ALL, ".866");
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hCon, &info); // Получаем информацию о позиции курсора
    COORD cPos = {info.dwCursorPosition.X, info.dwCursorPosition.Y}; // запоминаем ее
	cPos.X = (80 - strlen(" "));
	SetConsoleCursorPosition(hCon, cPos);
	cout << (char)186;
	cout << (char)186;
	cout << cardsum;
	cPos.X = (80 - strlen(" "));
	cPos.Y++;
	SetConsoleCursorPosition(hCon, cPos);
	cout << (char)186;
	cPos.Y++;
	cPos.X=0;
	SetConsoleCursorPosition(hCon, cPos);
	cout << (char)199;
	setlocale(LC_ALL, ".866");
	for (int j = 0; j < 78; j++)
	{
		cout << (char)196;
	}
	cout << (char)182;
	cout << (char)186;
	setlocale(LC_ALL, "Russian");
	cout << "Введите сумму: ";
	setlocale(LC_ALL, ".866");
	cPos.Y++;
	cPos.X = (80 - strlen(" "));
	SetConsoleCursorPosition(hCon, cPos);
	cout << (char)186;
	cPos.Y++;
	cout << (char)186;
	cPos.X = (80 - strlen(" "));
	SetConsoleCursorPosition(hCon, cPos);
	cout << (char)186;
	cout << (char)200;
	for (int j = 0; j < 78; j++)
	{
		cout << (char)205;
	}
	cout << (char)188;
		cPos.X = (1);
		SetConsoleCursorPosition(hCon, cPos);
		string sumstr;
		getline(cin, sumstr);
		if(sumstr.empty())
		while((sumstr.empty()))
		{
			cPos.X = (1);
			SetConsoleCursorPosition(hCon, cPos);
			getline(cin, sumstr);
		}
		//cPos.Y++;
		//cPos.X=0;
		//SetConsoleCursorPosition(hCon, cPos);
		//cout << char(199);
		//cPos.X = (80 - strlen(" "));
		//SetConsoleCursorPosition(hCon, cPos);
		//cout << char(182);
		//cPos.Y++;
		//cPos.X=0;
		//SetConsoleCursorPosition(hCon, cPos);
		sum=atoi(sumstr.c_str());
	if(sum>cardsum) 
	{
		/*setlocale(LC_ALL, ".866");
		for (int j = 0; j < 80; j++)
		{
			cout << (char)196;
		}*/
		setlocale(LC_ALL, "Russian");
		SetConsoleTextAttribute(hCon, 224);
		cout << endl << "Введенная сумма превышает сумму, которую можно снять с данной карточки          ";
		SetConsoleTextAttribute(hCon, 7);
	}
	else
	{
	int newsum = sum, index = 0, n = 0;
	bool found = false, correct = true, perep = false;
	if (calc(m, mtemp, count, sum, newsum, index, found, correct, n, perep) == 2) 
	{
		/*setlocale(LC_ALL, ".866");
		for (int j = 0; j < 80; j++)
		{
			cout << (char)196;
		}*/
		setlocale(LC_ALL, "Russian");
		SetConsoleTextAttribute(hCon, 192); 
		cout << endl << "Некорректная сумма                                                              ";
		SetConsoleTextAttribute(hCon, 7);
	}
	else 
	if (calc(m, mtemp, count, sum, newsum, index, found, correct, n, perep) == 1)
	{
		newsum = sum, index = 0, n = 0, found = false, correct = true, perep = false;
		outmoney(m, mtemp, count, sum, newsum, index, found, correct, n, perep);
			ofstream fout("money.txt");
	for (int i = 0; i < count; i++)
	{
		fout << m[i].cost << " ";
		fout << m[i].count;
		fout << endl;
	}
	data *dt = new data[1];
	string c;
	int count=0;
	ifstream temp("temp.txt");
	temp >> dt[0].ATR;
	temp >> dt[0].capdu;
	temp >> dt[0].rapdu;
	temp.close();
	ifstream cards1("cards.txt");
	while(cards1 >> c)
	{
		count++;
	}
	cards1.close();
	count/=6;
	cardsData *dtc = new cardsData[count];
	ifstream cards2("cards.txt");
	for(int i=0; i<count; i++)
	{
		cards2 >> dtc[i].ATR;
		cards2 >> dtc[i].capdu;
		cards2 >> dtc[i].rapdu;
		cards2 >> dtc[i].PIN;
		cards2 >> dtc[i].counter;
		cards2 >> dtc[i].moneycount;
	}
	int i0=-1;
	for(int i=0; i<count; i++)
	{
		if(dt[0].ATR==dtc[i].ATR && dt[0].capdu==dtc[i].capdu && dt[0].rapdu==dtc[i].rapdu) i0=i;
	}
	dtc[i0].moneycount-=sum;
	ofstream cardsMoney("cards.txt");
	for(int i=0; i<count; i++)
	{
		cardsMoney << dtc[i].ATR << endl;
		cardsMoney << dtc[i].capdu << endl;
		cardsMoney << dtc[i].rapdu << endl;
		cardsMoney << dtc[i].PIN << endl;
		cardsMoney << dtc[i].counter << endl;
		cardsMoney << dtc[i].moneycount << endl;
	}
	ofstream temp0("temp.txt");
	temp0.close();
	}
	}
	}
	else if(tempcard==2)
	{
		Sleep(10000);
		continue;
	}
	else if(tempcard==3)
	{
		Sleep(10000);
		continue;
	}
	else if(tempcard==4)
	{
		Sleep(10000);
		continue;
	}
	Sleep(10000);
	system("cls");
}

	system("pause");
	return 0;
}
