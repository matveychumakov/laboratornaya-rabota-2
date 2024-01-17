#include "modAlphaCipher.h"
modAlphaCipher::modAlphaCipher(const wstring& skey)
{
	for (unsigned i=0; i<numAlpha.size(); i++) {
		alphaNum[numAlpha[i]]=i;
	}
	key = convert(getValidKey(skey));;
}
//прием ключа, конвертация и использование в шифровании

wstring modAlphaCipher::encrypt(const wstring& open_text)
{
	vector<int> work = convert(getValidOpenText(open_text));
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
	}
	return convert(work);
}
//прием текста и шифрование с помощью сложения значения с элементом ключа 

wstring modAlphaCipher::decrypt(const wstring& cipher_text)
{
	vector<int> work = convert(getValidCipherText(cipher_text));
	for(unsigned i=0; i < work.size(); i++) {
		work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
	}
	return convert(work);
}
// расшифрование текста с помощью вычитания из значения элемента ключа  

inline vector<int> modAlphaCipher::convert(const wstring& s)
{
	vector<int> result;
	for(auto c:s) {
		result.push_back(alphaNum[c]);
	}
	return result;
}
//преобразование входной строки в вектор

inline wstring modAlphaCipher::convert(const vector<int>& v)
{
	wstring result;
	for(auto i:v) {
		result.push_back(numAlpha[i]);
	}
	return result;
}
//преобразование входного вектора в широкую строку 

inline wstring modAlphaCipher::getValidKey(const wstring & s)
{
	if (s.empty())
		throw cipher_error("empty key"); //если ключ пуст -> вывод 
	wstring tmp(s);
	string ws = codec.to_bytes(s);
	for (auto & c:tmp) {
		if (!iswalpha(c))
			throw cipher_error(std::string("entered key is invalid ")+ws); //если символ != буква -> вывод
		if (iswlower(c))
			c = towupper(c); //если символ строчный -> преобразуем его в ЗАГЛАВНЫЙ
	}
	return tmp;
}
//проверка и преобразование ключа

inline wstring modAlphaCipher::getValidOpenText(const wstring & s)
{
	wstring tmp;
	for (auto c:s) {
		if (iswalpha(c)) {
			if (iswlower(c))
				tmp.push_back(towupper(c)); //если символ буква -> если строчный ----> в заглавный
			else
				tmp.push_back(c);
		}
	}
	if (tmp.empty())
		throw cipher_error("text is empty"); //если в tmp ничего нет -> ошибка
	return tmp;
}
//преобразование текста и проверка

inline wstring modAlphaCipher::getValidCipherText(const wstring & s)
{
	if (s.empty())
		throw cipher_error("text is empty ");
	for (auto c:s) {
		string ws = codec.to_bytes(s);
		if (!iswupper(c))
			throw cipher_error(std::string("invalid text ")+ws); //если символ не заглавный -> ошибка
	}
	return s;
}
//проверка шифрованного текста 
