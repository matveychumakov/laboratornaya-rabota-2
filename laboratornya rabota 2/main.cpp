#include <iostream>
#include <cctype>
#include "modAlphaCipher.h"
#include <locale>
using namespace std;

void check(const wstring& Text, const wstring& key, const bool destructCipherText=false)
{
	try {
		wstring cipherText; 
		wstring decryptedText;
		modAlphaCipher cipher(key);
		cipherText = cipher.encrypt(Text); // зашифрование текста 
		if (destructCipherText)
			cipherText.front() = towlower(cipherText.front()); // первый символ в нижний регистр елси destuctciphertext = True
		decryptedText = cipher.decrypt(cipherText); // расшифрование cipherText 
		wcout<<"ключ:"<<key<<endl;
		wcout<<Text<<endl;
		wcout<<cipherText<<endl;
		wcout<<decryptedText<<endl;
	} catch (const cipher_error & e) {
		wcerr<<"error: "<<e.what()<<endl;
	}
}

int main()
{
	locale loc("ru_RU.UTF-8");
	locale::global(loc);
	check(L"молоко внутри пакета с молоком",L"пластиковый");
	wcout << "-------------" << endl;
	check(L"МОЛОКОВНУТРИПАКЕТАСМОЛОКОМ",L"");
	wcout << "-------------" << endl;
	check(L"МОЛОКОВНУТРИПАКЕТАСМОЛОКОМ",L"Е100-Е182");
	wcout << "-------------" << endl;
	check(L"МОЛОКОВНУТРИПАКЕТАСМОЛОКОМ",L"ВКУСНОЕ");
	wcout << "-------------" << endl;
	check(L"МОЛОКОВНУТРИПАКЕТАСМОЛОКОМ",L"ЙЦУ",true);
	wcout << "-------------" << endl;
	check(L"№;%?:*()446484,,,,,,,,,",L"ЙЦУ");
	return 0;
}
