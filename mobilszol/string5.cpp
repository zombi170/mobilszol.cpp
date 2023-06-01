#include <iostream>
#include <cstring>

#include "memtrace.h"
#include "string5.h"

String::String (char const* s) :len(strlen(s)){
    pData = new char[len + 1];
    strcpy(pData, s);
}

String::String (String const& copy) :len(copy.len){
    pData = new char[len + 1];
    strcpy(pData, copy.pData);
}

String& String::operator=(String const& rhs){
    if (this != &rhs){
        delete[] pData;     ///< destruktor
        len = rhs.len;      ///< copy konstruktor
        pData = new char[len + 1];
        strcpy(pData, rhs.pData);
    }
    return *this;       ///< visszatérés, hogy láncolható legyen
}

bool String::operator==(const String& rhs) const{
    return strcmp(pData, rhs.pData) == 0;
}

bool String::operator!=(const String& rhs) const{
    return !(*this == rhs);
}

String String::operator+(const char& s) const{
    String uj;
    uj.len = len + 1;
    delete[] uj.pData;
    uj.pData = new char[uj.len + 1];
    strcpy(uj.pData, pData);
    uj.pData[len] = s;
    uj.pData[uj.len] = '\0';
    return uj;
}

String String::operator+(String const& str) const{
    String uj;
    uj.len = len + str.len;
    delete[] uj.pData;
    uj.pData = new char[uj.len + 1];
    strcpy(uj.pData, pData);
    strcat(uj.pData,str.pData);
    return uj;
}

std::ostream& operator<<(std::ostream& os, String const& str){
    os << str.c_str();
    return os;
}

std::istream& operator>>(std::istream& is, String& s0) {
    unsigned char ch;
    s0 = String("");            ///< üres string, ehhez fűzünk hozzá
    std::ios_base::fmtflags fl = is.flags(); ///< eltesszük a régi flag-eket
    is.setf(std::ios_base::skipws);			///< az elején eldobjuk a ws-t
    while (is >> ch) {
        is.unsetf(std::ios_base::skipws);	///< utána pedig már nem
        if (isspace(ch)) {
            is.putback(ch);             ///< na ezt nem kérjük
            break;
        }
        else {
            s0 = s0 + ch;               ///< végére fűzzük a karaktert
        }
    }
    is.setf(fl);						///< visszaállítjuk a flag-eket
    return is;
}

