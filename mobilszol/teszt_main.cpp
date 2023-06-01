#include <iostream>

#include "memtrace.h"
#include "gtest_lite.h"
#include "lista.h"

#ifndef CPORTA
#define CPORTA
#endif

#ifndef MEMTRACE
#define MEMTRACE
#endif

#ifndef TESZTEK
#define TESZTEK  true
#endif

int main(){
#if TESZTEK == true
    TEST (Test1, Sztringmuveletek){
            String a("abc");
            String b;
            EXPECT_STREQ("abc", a.c_str()) << "Hiba az egyparameteres konstruktorban" << std::endl;
            EXPECT_STREQ("\0", b.c_str()) << "Hiba a parameter nelkuli konstruktorban" << std::endl;
            String c = b;
            EXPECT_STREQ("\0", c.c_str()) << "Hiba a masolo konstruktorban" << std::endl;
            c = a;
            EXPECT_STREQ("abc", c.c_str()) << "Hibas operator=" << std::endl;
            b = b + 'd';
            EXPECT_STREQ("d", b.c_str()) << "Hibas operator+ (karakter)" << std::endl;
            a = a + b;
            EXPECT_STREQ("abcd", a.c_str()) << "Hibas operator+ (String)" << std::endl;
            EXPECT_EQ(false, a == c) << "Hibas operator==" << std::endl;
            EXPECT_EQ(true, a != c) << "Hibas operator==" << std::endl;
            c = a;
            EXPECT_EQ(true, a == c) << "Hibas operator==" << std::endl;
            std::stringstream os;
            os << a;
            EXPECT_STREQ("abcd", os.str().c_str()) << "Hibas operator<< (kiiras)" << std::endl;
            std::stringstream is("   hello   nn");
            is >> b;
            EXPECT_STREQ("hello", b.c_str()) << "Hibas operator>> (beolvasas)" << std::endl;
    } END

    TEST (Test2, Ugyfel_kibe){
            Ugyfel bela("+36706669999", 2,"Kiss-Kovacs Bela", 5,
                        "7634 Pecs, Forras u. 69.", 'S');
            std::ofstream ofajl("test2.txt");
            ofajl << "Ugyfelek" << std::endl;
            ASSERT_NO_THROW(bela.kiir(ofajl))
            ofajl.close();

            String str;
            String ugy("Ugyfelek");
            std::ifstream fajl("test2.txt");
            (fajl >> str).ignore(1);
            EXPECT_NO_THROW(if (str != ugy)
                                throw std::invalid_argument("Rossz fajl!");) << "Rossz fajlbol olvasott" << std::endl;
            Ugyfel uj;
            ASSERT_NO_THROW(uj.beolvas(fajl))
            fajl.close();

            EXPECT_STREQ("+36706669999", uj.getID().c_str()) << "Hibas az ID" << std::endl;
            EXPECT_STREQ("Kiss-Kovacs Bela", uj.getNev().c_str()) << "Hibas a nev" << std::endl;
            EXPECT_STREQ("7634 Pecs, Forras u. 69.", uj.getCim().c_str()) << "Hibas a cim" << std::endl;
            EXPECT_EQ('S', uj.getCsomag()->getID()) << "Hibas a csomag" << std::endl;
            EXPECT_THROW(uj.setCsomag('Z'),std::invalid_argument&) << "Nem jo a hibakezeles a setCsomag()-ban" << std::endl;
    } END

    TEST (Test3, Forgalom_kibe){
            Forgalom feri("06705553434", 55, 69);
            std::ofstream ofajl("test3.txt");
            ofajl << "Forgalom" << std::endl;
            ASSERT_NO_THROW(feri.kiir(ofajl))
            ofajl.close();

            String str;
            String forg("Forgalom");
            std::ifstream fajl("test3.txt");
            (fajl >> str).ignore(1);
            EXPECT_NO_THROW(if (str != forg)
                                throw std::invalid_argument("Rossz fajl!");) << "Rossz fajlbol olvasott" << std::endl;
            Forgalom uj;
            ASSERT_NO_THROW(uj.beolvas(fajl))
            fajl.close();
            EXPECT_STREQ("06705553434", uj.getID().c_str()) << "Hibas az ID" << std::endl;
            EXPECT_EQ((size_t)55, uj.getSMS()) << "Hibas az SMS" << std::endl;
            EXPECT_EQ((size_t)69, uj.getPerc()) << "Hibas a Perc" << std::endl;
    } END

    TEST (Test4, Lista){
            ASSERT_NO_THROW(Lista lista("ugyfelek.txt", "forgalom.txt"))
            Lista lista("ugyfelek.txt", "forgalom.txt");
            Ugyfel uj("+36305652323", 2, "Uj Ugyfel", 5, "1111 Budapest, Pelda u. 33.", 'A');
            Forgalom ujf("+36305652322", 55, 66);
            EXPECT_THROW(lista.hozzaad(uj, ujf), std::logic_error&) << "Hiba: eltero ID-kat adott hozza a listahoz" << std::endl;
            ujf.setID("+36305652323");
            String a("+36305652323");
            ASSERT_NO_THROW(lista.hozzaad(uj, ujf))
            EXPECT_THROW(lista.hozzaad(uj, ujf), std::logic_error&) << "Hiba: mar letezo ID-t adott hozza a listahoz" << std::endl;
            EXPECT_STREQ(lista.keres(a).ugyfel.getID().c_str(),"+36305652323") << "Hiba: Nem talaljuk az elemet" << std::endl;
            ASSERT_NO_THROW(lista.torol(a))
            EXPECT_THROW(lista.torol(a), std::invalid_argument&) << "Hiba: nem letezo elem torlese" << std::endl;
            String b("06201112222");
            ASSERT_NO_THROW(lista.torol(b))
            EXPECT_THROW(lista.keres(b), std::invalid_argument&) << "Hiba: nem letezo elemet talaltunk" << std::endl;
    } END

    TEST (Test5, Dijcsomagok){
            Lista lista("ugyfelek.txt", "forgalom.txt");
            String a("06302223333");
            String b("06201112222");
            String c("06703334444");
            EXPECT_EQ((size_t)12840, lista.havidij(a)) << "Hibas az Alap csomag kalkulator" << std::endl;
            EXPECT_EQ((size_t)25620, lista.havidij(b)) << "Hibas az SMSMax csomag kalkulator" << std::endl;
            EXPECT_EQ((size_t)26420, lista.havidij(c)) << "Hibas az MobilNet csomag kalkulator" << std::endl;
    } END
#endif
    char menu = '0';
    Lista lista("ugyfelek.txt", "forgalom.txt");
    String input;
    char m = '0';
    while(menu != '9'){
        std::cout << std::endl << "1. Adatok kiirasa" << std::endl;
        std::cout << "2. Ugyfel havidija" << std::endl;
        std::cout << "3. Uj Ugyfel felvetele" << std::endl;
        std::cout << "4. Ugyfel adatainak modositasa" << std::endl;
        std::cout << "5. Ugyfel torlese" << std::endl;
        std::cout << "9. Kilepes" << std::endl;

        std::cin >> std::ws;
        (std::cin >> menu).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        try {
            switch (menu) {
                case '1':
                    try{
                        lista.kiir();
                    }
                    catch (const std::invalid_argument& hiba){
                        std::cout << hiba.what() << std::endl;
                    }
                    break;

                case '2':
                    try{
                        std::cout << "Adja meg az Ugyfel azonositot: ";
                        std::cin >> std::ws;
                        (std::cin >> input).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << lista.havidij(input) << " Ft" << std::endl;
                    }
                    catch (const std::invalid_argument& hiba){
                        std::cout << hiba.what() << std::endl;
                    }
                    break;

                case '3':
                    try{
                        Ugyfel uj;
                        uj.felvesz();
                        Forgalom ujf;
                        ujf.felvesz(uj.getID());
                        lista.hozzaad(uj, ujf);
                        std::cout << "Sikeres felvetel!" << std::endl;
                    }
                    catch (const std::invalid_argument& hiba){
                        std::cout << hiba.what() << std::endl;
                    }
                    catch (const std::logic_error& hiba){
                        std::cout << hiba.what() << std::endl;
                    }
                    break;

                case '4':
                    std::cout << "Adja meg a modositando Ugyfel azonositojat: ";
                    std::cin >> std::ws;
                    (std::cin >> input).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    while (m != '9'){
                        std::cout << "Mit szeretne modositani?" << std::endl;
                        std::cout << "1. Azonosito" << std::endl;
                        std::cout << "2. Nev" << std::endl;
                        std::cout << "3. Cim" << std::endl;
                        std::cout << "4. Csomag" << std::endl;
                        std::cout << "5. SMS forgalom" << std::endl;
                        std::cout << "6. Hivas forgalom" << std::endl;
                        std::cout << "9. Semmit" << std::endl;
                        std::cin >> std::ws;
                        (std::cin >> m).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        try{
                            if (m != '9'){
                                input = lista.keres(input).modosit(m, lista, input);
                                std::cout << "Sikeres modositas!" << std::endl;
                            }
                        }
                        catch (const std::invalid_argument& hiba){
                            std::cout << hiba.what() << std::endl;
                        }
                        catch (const std::logic_error& hiba){
                            std::cout << hiba.what() << std::endl;
                        }
                    }
                    break;

                case '5':
                    try{
                        std::cout << "Adja meg a torlendo Ugyfel azonositojat: ";
                        std::cin >> std::ws;
                        (std::cin >> input).ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        lista.torol(input);
                        std::cout << "Sikeres torles!" << std::endl;
                    }
                    catch (const std::invalid_argument& hiba){
                        std::cout << hiba.what() << std::endl;
                    }
                    break;

                case '9':
                    lista.mentes();
                    std::cout << "Mentes!" << std::endl;
                    break;

                default:
                    throw std::out_of_range("Hibas input a menuben");
            }
        }
        catch (const std::out_of_range& hiba){
            std::cout << hiba.what() << std::endl;
        }
        catch (const std::bad_alloc& hiba){
            std::cout << "Nem sikerult memoriat foglalni" << std::endl;
        }
        catch (...){
            std::cout << "Varatlan hiba" << std::endl;
        }
    }
}