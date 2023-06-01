#include "memtrace.h"
#include "forgalom.h"

void Forgalom::beolvas(std::ifstream& fajl){
    /// ID beolvasása
    String str;
    (fajl >> str).ignore(1);
    setID(str);

    /// Küldött SMS-ek számának beolvasása
    size_t db;
    (fajl >> db).ignore(1);
    setSMS(db);

    /// Lebeszélt percek számának beolvasása
    (fajl >> db).ignore(1);
    setPerc(db);
}

void Forgalom::kiir(std::ofstream& fajl) const{
    fajl << getID() << ' ';
    fajl << getSMS() << ' ';
    fajl << getPerc() << std::endl;
}

void Forgalom::felvesz(const String& id){
    /// ID beállítása
    setID(id);

    /// Küldött SMS-ek számának beolvasása
    size_t db;
    std::cout << "Adja meg a havi elkuldott SMS-ek szamat: ";
    std::cin >> std::ws;
    if (std::cin.peek() > '9' || std::cin.peek() < '0'){
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Nem szamot adott meg!");
    }
    (std::cin >> db).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    setSMS(db);

    /// Lebeszélt percek számának beolvasása
    std::cout << "Adja meg a havi lebeszelt percek szamat: ";
    std::cin >> std::ws;
    if (std::cin.peek() > '9' || std::cin.peek() < '0'){
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Nem szamot adott meg!");
    }
    (std::cin >> db).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    setPerc(db);
}

std::ostream& operator<<(std::ostream& os, const Forgalom& forg){
    os << forg.getID() << " \t";
    os << forg.getSMS() << "db SMS\t";
    os << forg.getPerc() << " Perc" << std::endl;
    return os;
}