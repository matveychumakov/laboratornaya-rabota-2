#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>
#include <codecvt>
using namespace std;
class modAlphaCipher
{
private:
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> codec;
	wstring numAlpha =L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; //алфавит по порядку
	map <wchar_t,int> alphaNum; //ассоциативный массив "номер по символу"
	vector <int> key; //ключ
	vector<int> convert(const wstring& s); //преобразование строка-вектор
	wstring convert(const vector<int>& v); //преобразование вектор-строка
	wstring getValidKey(const wstring & s); // проверка ключа
	wstring getValidOpenText(const wstring & s); // проверка текста
	wstring getValidCipherText(const wstring & s); //проверка зашифрованного текста
public:
	modAlphaCipher()=delete; //запретим конструктор без параметров
	modAlphaCipher(const wstring& skey); //конструктор для установки ключа
	wstring encrypt(const wstring& open_text); //зашифрование
	wstring decrypt(const wstring& cipher_text);//расшифрование
};

class cipher_error: public invalid_argument
{
public:
	explicit cipher_error (const string& what_arg):
		invalid_argument(what_arg) {}
	explicit cipher_error (const char* what_arg):
		invalid_argument(what_arg) {}
};
