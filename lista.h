#ifndef MOBILSZOL_LISTA_H
#define MOBILSZOL_LISTA_H

#include "ugyfel.h"
#include "forgalom.h"

/// Lista osztály mindkét fajta adathalmaz tárolásásra.
class Lista{
    /** @struct ListaElem osztály, a Listában lévő elemek, amikben találhatóak az adatok. */
    struct ListaElem{
        Ugyfel ugyfel;      ///< Egy ügyfél adatai.
        Forgalom forgalom;  ///< A fentebbi ügyfél forgalma az adott hónapban.
        ListaElem* next;    ///< A következő elemre mutató pointer (nullptr, ha nincs következő).

        /// ListaElem konstruktor
        ListaElem() :next(nullptr) {
            ugyfel = Ugyfel();
            forgalom = Forgalom();
        }

        /** ListaElem adatainak a módosítását végzi
         * @param m A módosítani kívánt része a ListaElemnek, amit egy char referenciával döntünk el.
         * @param lista A lista referenciája, amiben módosítjuk az elemet.
         * @param id Az azonosító referenciája, hogy melyik ListaElemet kívánjuk módosítani.
         * @return A módosított (vagy nem módosított) azonosító.
         * @throw std::logic_error Ha létezik már az azonosító.
         * @throw std::invalid_argument Ha rossz a névnek vagy a címnek a megadása, ha szám helyett nem számot kap, vagy ha hibás az input.
         */
        String modosit(const char& m, Lista& lista, const String& id);
    };

    ListaElem* begin;   ///< Lista kezdetére mutató pointer.
public:
    /** Lista konstruktor
     * @param u_fajl Az Ügyfeleket tartalmazó fájl névre mutató pointer.
     * @param f_fajl A havi Forgalmat tartalmazó fájl névre mutató pointer.
     * @throw std::invalid_argument Ha rossz fájlokat kapott a függvény.
     */
    Lista(const char* u_fajl, const char* f_fajl);

    /// Kiírja a Lista összes elemét
    void kiir() const;

    /** Megkeres egy ListaElemet a Listából (azonosító alapján)
     * @param keres A keresendő ListaElem azonosító referenciája.
     * @return A megtalált ListaElem referenciája.
     * @throw std::invalid_argument Ha nem található az azonosító.
     */
    ListaElem& keres(const String& keres);

    /** Hozzáad a Listához egy ListaElemet
     * @param ugy Az Ügyfél referenciája, akit hozzá kívánunk adni az adaatbázishoz.
     * @param forg A havi Forgalom refernciája.
     * @throw std::logic_error Ha nem egyezik az Ügyfél és a Forgalom osztály azonosítója vagy ha már van ilyen azonosító.
     */
    void hozzaad(const Ugyfel& ugy, const Forgalom& forg);

    /** Töröl egy elemet a Listából (azonosító alapján)
     * @param torles A törlendő Ügyfél azonosító referenciája.
     * @throw std::invalid_argument Ha nem található az azonosító.
     */
    void torol(const String& torles);

    /** Megadja egy adott Ügyfél havidíját a Díjcsomagja és a Forgalma alapján a Listában (azonosító alapján)
     * @param azon Az Ügyfél azonosítója, akinek a havi forgalmát szeretnénk megtudni.
     * @return Az össz havidíj értéke.
     */
    inline size_t havidij(const String& azon){
        ListaElem* ptr = &keres(azon);
        size_t sum = ptr->ugyfel.getCsomag()->dijkalkulator(ptr->forgalom);
        return sum;
    }

    /// Elmenti a Lista elemeit az eredeti fájlokba
    void mentes() const;

    /// Destruktor
    ~Lista();
};

#endif //MOBILSZOL_LISTA_H
