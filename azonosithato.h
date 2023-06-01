#ifndef MOBILSZOL_AZONOSITHATO_H
#define MOBILSZOL_AZONOSITHATO_H

#include "string5.h"

/// Ősosztálya az Ügyfélnek és a Forgalomnak, mivel mindkettő ugyanazzal az azonosítóval működik. Absztrakt osztály.
class Azonosithato{
    String id;  ///< Azonosítója az Ügyfél és a Forgalom osztályoknak
public:
    /** Konstruktor
     * @param azon Azonosítóra mutató pointer.
     */
    inline explicit Azonosithato(const char* azon = "") :id(azon) {}

    /** Visszaadja az id Stringet
     * @return Azonosító értéke.
     */
    inline String getID() const{ return id;}

    /** Beállítja az id Stringet
     * @param azon Azonosító referenciája.
     */
    inline void setID(const String& azon) { id = azon;}
    /** Beállítja az id Stringet
     * @param azon Azonosítóra mutató pointer.
     */
    inline void setID(const char* azon) { String uj(azon); id = uj;}

    /** Virtuális beolvasó függvény,
     * amely referenciaként kapott fájlból olvassa be az osztály létrehozásához szükséges adatokat.
     * A leszármazottak határozzák meg ennek a belső működését,
     * mivel önmagában nincs értelme ennél az alaposztálynál.
     * @param fajl A fájlból beolvasó stream referenciája.
     */
    virtual void beolvas(std::ifstream& fajl) = 0;

    /** Virtuális kiíró függvény,
     * amely referenciaként kapott fájlba írja be az osztályban lévő adatokat.
     * A leszármazottak határozzák meg ennek a belső működését,
     * mivel önmagában nincs értelme ennél az alaposztálynál.
     * @param fajl A fájlba kiíró stream referenciája.
     */
     virtual void kiir(std::ofstream& fajl) const = 0;

     /// Virtuális destruktor
     virtual ~Azonosithato() = default;
};

#endif //MOBILSZOL_AZONOSITHATO_H
