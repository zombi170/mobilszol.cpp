#include "memtrace.h"
#include "ugyfel.h"

Ugyfel& Ugyfel::operator=(const Ugyfel& rhs){
    if (this != &rhs) {
        setID(rhs.getID());
        n_db = rhs.n_db;
        nev = rhs.nev;
        c_db = rhs.c_db;
        cim = rhs.cim;
        if (rhs.csomag != nullptr)
            setCsomag(rhs.getCsomag()->getID());
        else
            csomag = nullptr;
    }
    return *this;
}

void Ugyfel::setCsomag(const char& c){
    if (c == 'A' || c == 'a'){
        if (csomag != nullptr)
            delete csomag;
        csomag = new Alap();
    }
    else if (c == 'S' || c == 's'){
        if (csomag != nullptr)
            delete csomag;
        csomag = new SMSMax();
    }
    else if (c == 'M' || c == 'm'){
        if (csomag != nullptr)
            delete csomag;
        csomag = new MobilNet;
    }
    else
        throw std::invalid_argument("Nem letezo csomag!");
}

void Ugyfel::beolvas(std::ifstream& fajl){
    /// ID beolvasása
    String str;
    (fajl >> str).ignore(1);
    setID(str);

    /// Név beolvasása
    size_t db;
    String temp;
    (fajl >> db).ignore(1);
    if (db <= 0)
        throw std::invalid_argument("Nincs neve!");
    for (size_t i = 0; i < db; i++){
        (fajl >> str).ignore(1);
        temp = temp + str;
        if ((i+1) != db)
            temp = temp + ' ';
    }
    setNev(temp, db);

    /// Cím beolvasása
    (fajl >> db).ignore(1);
    if (db < 5)
        throw std::invalid_argument("Nem megfelelo a lakcim merete!");
    (fajl >> str).ignore(1);
    temp = str;
    temp = temp + ' ';
    for (size_t i = 1; i < db; i++){
        (fajl >> str).ignore(1);
        temp = temp + str;
        if ((i+1) != db)
            temp = temp + ' ';
    }
    setCim(temp, db);

    /// Csomag beolvasása
    char c;
    (fajl >> c).ignore(1);
    setCsomag(c);
}

void Ugyfel::kiir(std::ofstream& fajl) const{
    fajl << getID() << ' ';
    fajl << n_db << ' ';
    fajl << getNev() << ' ';
    fajl << c_db << ' ';
    fajl << getCim() << ' ';
    fajl << getCsomag()->getID() << std::endl;
}

void Ugyfel::felvesz(){
    String input;

    /// ID beolvasása
    std::cout << "Adja meg az Ugyfel azonositot: ";
    std::cin >> std::ws;
    (std::cin >> input).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    setID(input);

    /// Név beolvasása
    String temp;
    size_t db = 0;
    std::cout << "Adja meg az Ugyfel nevet: ";
    std::cin >> std::ws;
    while (std::cin.peek() != '\n'){
        if (db > 0)
            temp = temp + ' ';
        std::cin >> input;
        temp = temp + input;
        db++;
    }
    if (db <= 0)
        throw std::invalid_argument("Nincs neve!");
    setNev(temp, db);

    /// Cím beolvasása
    String tmp;
    db = 0;
    std::cout << "Adja meg az Ugyfel cimet: ";
    std::cin >> std::ws;
    while (std::cin.peek() != '\n'){
        if (db > 0)
            tmp = tmp + ' ';
        std::cin >> input;
        tmp = tmp + input;
        db++;
    }
    if (db < 5)
        throw std::invalid_argument("Nem megfelelo a lakcim merete!");
    setCim(tmp, db);

    /// Csomag beolvasása
    char c;
    std::cout << "Adja meg az Ugyfel dijcsomagjat (csak a kezdobetujet): ";
    std::cin >> std::ws;
    (std::cin >> c).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    setCsomag(c);
}

std::ostream& operator<<(std::ostream& os, const Ugyfel& ugy){
    os << ugy.getID() << " \t";
    os << ugy.getNev() << " \t";
    os << ugy.getCim() << " \t";
    if (ugy.getCsomag()->getID() == 'A')
        os << "Alap";
    else if (ugy.getCsomag()->getID() == 'S')
        os << "SMSMax";
    else if (ugy.getCsomag()->getID() == 'M')
        os << "MobilNet";
    else
        throw std::invalid_argument("Nem letezo csomag");
    os << std::endl;
    return os;
}