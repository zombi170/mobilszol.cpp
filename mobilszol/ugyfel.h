#ifndef MOBILSZOL_UGYFEL_H
#define MOBILSZOL_UGYFEL_H

#include "azonosithato.h"
#include "dijcsomagok.h"

/** Egy adott Ügyfél adatait tároló osztály, amely az Azonosítható osztályból származik le.
 * Tárolja: hány darab névből áll a teljes neve(nevek, amelyekben kötőjel szerepel egynek számít pl: Moholy-Nagy),
 *          teljes nevet, teljes lakcímet, illetve a díjcsomagját.
 */
class Ugyfel :public Azonosithato{
    size_t n_db;    ///< Teljes név részeinek száma
    String nev;     ///< Teljes név
    size_t c_db;    ///< Teljes cím részeinek száma
    String cim;     ///< Teljes cím
    Alap* csomag;   ///< Díjcsomag osztályra mutató pointer
public:
    /// Paraméter nélküli konstruktor
    inline Ugyfel() :n_db(0), nev(), c_db(0), cim(), csomag(nullptr) {}
    /** Paraméteres konstruktor
     * @param id Az azonosítóra mutató pointer.
     * @param N A név részeinek száma.
     * @param name A teljes névre mutató pointer.
     * @param C A cím részeinek a száma.
     * @param add A teljes címre mutató pointer.
     * @param c A Díjcsomag karakter kód referenciája
     */
    inline explicit Ugyfel(const char* id, const size_t N, const char* name, const size_t C,
                    const char* add, const char& c)
            :Azonosithato(id), n_db(N), nev(name), c_db(C), cim(add), csomag(nullptr) {
        setCsomag(c);
    }

    /** Értékadó operator
     * @param rhs A másolandó Ügyfél osztály referenciája.
     * @return A lemásolt Ügyfél osztály referenciája.
     */
    Ugyfel& operator=(const Ugyfel& rhs);

    /** Visszaadja a nevet
     * @return A teljes név.
     */
    inline String getNev() const{ return nev;}

    /** Visszaadja a címet
     * @return A teljes cím.
     */
    inline String getCim() const{ return cim;}

    /** Visszaadja a csomagot
     * @return A díjcsomagra mutató pointer.
     */
    inline Alap* getCsomag() const{ return csomag;}

    /** Beállítja a nevet
     * @param str A teljes név referenciája.
     * @param n A név részeinek száma.
     */
    inline void setNev(const String& str, const size_t n) { nev = str; n_db = n;}

    /** Beállítja a címet
     * @param str A teljes cím referenciája.
     * @param c A cím részeinek száma.
     */
    inline void setCim(const String& str, const size_t c) { cim = str; c_db = c;}

    /** Beállítja a csomagot
     * @param c A díjcsomag karakter kódjának referenciája.
     * @throw std::invalid_argument Ha nem létezik a díjcsomag vagy rossz kódot kapott a függvény.
     */
    void setCsomag(const char& c);

    /** Beolvassa a fájlból az osztályhoz szükséges adatokat
     * @param fajl A fájlból beolvasó stream referenciája.
     * @throw std::invalid_argument Ha rossz a névnek vagy a címnek a megadása.
     */
    void beolvas(std::ifstream& fajl) override;

    /** Kiírja a fájlba az osztályban lévő adatokat
     * @param fajl A fájlba kiíró stream referenciája.
     */
    void kiir(std::ofstream& fajl) const override;

    /** Ügyfél felvétele
     * @throw std::invalid_argument Ha rossz a névnek vagy a címnek a megadása.
     */
    void felvesz();

    /// Destruktor
    inline ~Ugyfel() override{
        if (csomag != nullptr)
            delete csomag;
    }
};

/** Kiíró operator
 * @param os A kiíró stream referenciája.
 * @param ugy A kiírandó Ügyfél referenciája.
 * @return A kiíró stream referenciája (láncolhatóság miatt).
 * @throw std::invalid_argument Ha nem létezik a díjcsomag vagy rossz kódot kapott a függvény.
 */
std::ostream& operator<<(std::ostream& os, const Ugyfel& ugy);

#endif //MOBILSZOL_UGYFEL_H
