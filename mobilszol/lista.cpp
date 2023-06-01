#include "memtrace.h"
#include "lista.h"

String Lista::ListaElem::modosit(const char& m, Lista& lista, const String& id){
    String input;
    String temp;
    size_t db = 0;
    switch (m){
        case '1':
            std::cout << "Adja meg az Ugyfel azonositot: ";
            std::cin >> std::ws;
            (std::cin >> input).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            try{
                lista.keres(input);
                throw std::logic_error("Letezo azonosito");
            }
            catch (std::invalid_argument&){}
            ugyfel.setID(input);
            forgalom.setID(input);
            break;
        case '2':
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
            ugyfel.setNev(temp, db);
            break;
        case '3':
            std::cout << "Adja meg az Ugyfel cimet: ";
            std::cin >> std::ws;
            while (std::cin.peek() != '\n'){
                if (db > 0)
                    temp = temp + ' ';
                std::cin >> input;
                temp = temp + input;
                db++;
            }
            if (db < 5)
                throw std::invalid_argument("Nem megfelelo a lakcim merete!");
            ugyfel.setCim(temp, db);
            break;
        case '4':
            char c;
            std::cout << "Adja meg az Ugyfel dijcsomagjat (csak a kezdobetujet): ";
            std::cin >> std::ws;
            (std::cin >> c).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            ugyfel.setCsomag(c);
            break;
        case '5':
            std::cout << "Adja meg a havi elkuldott SMS-ek szamat: ";
            std::cin >> std::ws;
            if (std::cin.peek() > '9' || std::cin.peek() < '0'){
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Nem szamot adott meg!");
            }
            (std::cin >> db).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            forgalom.setSMS(db);
            break;
        case '6':
            std::cout << "Adja meg a havi lebeszelt percek szamat: ";
            std::cin >> std::ws;
            if (std::cin.peek() > '9' || std::cin.peek() < '0'){
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Nem szamot adott meg!");
            }
            (std::cin >> db).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            forgalom.setPerc(db);
            break;
        default:
            throw std::invalid_argument("Hibas input");
    }
    return ugyfel.getID();
}

Lista::Lista(const char* u_fajl, const char* f_fajl){
    String test;
    String ugy("Ugyfelek");
    String forg("Forgalom");

    /// Ügyfelek adatait tartalmazó fájl megnyitása
    std::ifstream ufajl(u_fajl);
    ufajl >> test;
    ufajl >> std::ws;
    if (test != ugy)
        throw std::invalid_argument("Rossz ugyfel fajlt adott meg!");

    /// Forgalom adatokat tartalmazó fájl megnyitása
    std::ifstream ffajl(f_fajl);
    ffajl >> test;
    ffajl >> std::ws;
    if (test != forg)
        throw std::invalid_argument("Rossz forgalom fajlt adott meg!");

    auto iter = new ListaElem;
    begin = iter;
    char c;

    /// Adatok beolvasása és Lista felépítése, amíg el nem fogy a fájl
    while ((ffajl >> c).peek() != EOF){
        ffajl.putback(c);
        iter->ugyfel.beolvas(ufajl);
        iter->forgalom.beolvas(ffajl);
        ffajl >> std::ws;
        if ((ffajl >> c).peek() != EOF){
            ffajl.putback(c);
            iter->next = new ListaElem;
            iter = iter->next;
        }
    }
}

void Lista::kiir() const{
    std::cout << std::endl << "Ugyfelek" << std::endl;
    ListaElem* iter = begin;

    /// Végigmegy az elemeken és kiírja azokat
    while (iter != nullptr){
        std::cout << iter->ugyfel;
        iter = iter->next;
    }

    std::cout << std::endl << "Forgalom" << std::endl;
    iter = begin;

    while (iter != nullptr){
        std::cout << iter->forgalom;
        iter = iter->next;
    }
}

Lista::ListaElem& Lista::keres(const String& keres){
    ListaElem* iter = begin;

    /// Megkeresi a keresendő elemet
    while (iter != nullptr && iter->ugyfel.getID() != keres){
        iter = iter->next;
    }

    if (iter == nullptr)    ///< Ha nem található az azonosító
        throw std::invalid_argument("Nem talalhato azonosito!");
    else
        return *iter;
}

void Lista::hozzaad(const Ugyfel& ugy, const Forgalom& forg){
    if (ugy.getID() != forg.getID())
        throw std::logic_error("Nem egyeznek az ID-k az Ugyfel es a Forgalom kozott");

    auto uj = new ListaElem;
    uj->ugyfel = ugy;
    uj->forgalom = forg;
    uj->next = nullptr;

    /// Elmegy a Lista végére és közben ellenőrzi, hogy létezik-e az azonosító már a listában
    if (begin == nullptr){  ///< Ha üres a Lista
        begin = uj;
    }
    else{   ///< Ha nem üres a Lista
        if (begin->ugyfel.getID() == uj->ugyfel.getID()){
            delete uj;
            throw std::logic_error("Mar letezik ez az ID");
        }
        ListaElem* iter = begin;
        while (iter->next != nullptr){
            if (iter->next->ugyfel.getID() == uj->ugyfel.getID()){
                delete uj;
                throw std::logic_error("Mar letezik ez az ID");
            }
            iter = iter->next;
        }
        iter->next = uj;
    }
}

void Lista::torol(const String& torles){
    ListaElem* inchworm = nullptr;
    ListaElem* iter = begin;

    /// Megkeresi a törlendő elemet
    while (iter != nullptr && iter->ugyfel.getID() != torles){
        inchworm = iter;
        iter = iter->next;
    }

    /// Törli az elemet és átállítja a pointereket
    if (iter == nullptr)    ///< Ha nem található az azonosító
        throw std::invalid_argument("Nem talalhato azonosito!");
    else if (inchworm == nullptr){  ///< Ha az első elemet kell törölni
        ListaElem* uj = iter->next;
        delete iter;
        begin = uj;
    }
    else{   ///< Ha más elemet kell törölni
        inchworm->next = iter->next;
        delete iter;
    }
}

void Lista::mentes() const{
    std::ofstream fajl("ugyfelek.txt");
    fajl << "Ugyfelek" << std::endl;
    ListaElem* iter = begin;

    /// Végigmegy az elemeken és kiírja azokat
    while (iter != nullptr){
        iter->ugyfel.kiir(fajl);
        iter = iter->next;
    }
    fajl.close();

    fajl.open("forgalom.txt");
    fajl << "Forgalom" << std::endl;
    iter = begin;

    while (iter != nullptr){
        iter->forgalom.kiir(fajl);
        iter = iter->next;
    }
    fajl.close();
}

Lista::~Lista(){
    ListaElem* iter = begin;
    ListaElem *kov;
    while (iter != nullptr){
        kov = iter->next;
        delete iter;
        iter = kov;
    }
}