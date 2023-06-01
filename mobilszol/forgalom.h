#ifndef MOBILSZOL_FORGALOM_H
#define MOBILSZOL_FORGALOM_H

#include "azonosithato.h"

/// Egy adott ügyfélnek az egy havi forgalmát tárolja az alábbi osztály, elküldött sms-ekben és lebeszélt percekben.
class Forgalom :public Azonosithato{
    size_t sms;     ///< Elküldött SMS-ek száma
    size_t perc;    ///< Lebeszélt percek száma
public:
    /** Konstruktor
     * @param id Az azonosítóra mutató pointer.
     * @param db A havi elküldött SMS-ek száma.
     * @param le A havi lebeszélt percek száma.
     */
    inline explicit Forgalom(const char* id = "", const size_t db = 0, const size_t le = 0)
            :Azonosithato(id), sms(db), perc(le) {}

    /** Visszaadja az elküldött SMS-ek számát
     * @return A havi elküldött SMS-ek száma.
     */
    inline size_t getSMS() const{ return sms;}

    /** Visszaadja a lebeszélt percek számát
     * @return A havi lebeszélt percek száma.
     */
    inline size_t getPerc() const{ return perc;}

    /** Beállítja az elküldött sms-ek számát
     * @param db A havi elküldött SMS-ek száma.
     */
    inline void setSMS(const size_t db) { sms = db;}

    /** Beállítja a lebeszélt percek számát
     * @param db A havi lebeszélt percek száma.
     */
    inline void setPerc(const size_t db) { perc = db;}

    /** Beolvassa a fájlból az osztályhoz szükséges adatokat
     * @param fajl A fájlból kiolvasó stream referenciája.
     */
    void beolvas(std::ifstream& fajl) override;

    /** Kiírja a fájlba az osztályban lévő adatokat
     * @param fajl A fájlból beolvasó stream referenciája.
     */
    void kiir(std::ofstream& fajl) const override;

    /** Forgalom felvétele
     * @param id A fájlba kiíró stream referenciája.
     * @throw std::invalid_argument Ha ahol számot vár a függvény, ott nem számot kap.
     */
    void felvesz(const String& id);
};

/** Kiíró operator
 * @param os A kiíró stream referenciája.
 * @param forg A kiírandó havi Forgalom referenciája.
 * @return A kiíró stream referenciája (láncolhatóság miatt).
 */
std::ostream& operator<<(std::ostream& os, const Forgalom& forg);

#endif //MOBILSZOL_FORGALOM_H
