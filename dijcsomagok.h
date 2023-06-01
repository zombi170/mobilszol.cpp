#ifndef MOBILSZOL_DIJCSOMAGOK_H
#define MOBILSZOL_DIJCSOMAGOK_H

#include "forgalom.h"

/// Alap díjcsomagosztály, amiből a többi származik le (akár bővíthető tovább is)
class Alap{
protected:
    char id;        ///< Kódja a díjcsomagnak (egy karakter)
    size_t smsdij;  ///< Egy SMS díja
    size_t percdij; ///< Egy megkezdett percnyi telefonbeszélgetés díja
public:
    /** Konstruktor
     * @param id Díjcsomag azonosító referenciája.
     * @param sms Az SMS díj értéke a csomagban.
     * @param perc A Percdíj értéke a csomagban.
     */
    inline explicit Alap(const char& id = 'A', size_t sms = 40, size_t perc = 20) :id(id), smsdij(sms), percdij(perc) {}

    /** Visszaadja a díjcsomag kódját
     * @return Azonosítója a díjcsomagnak.
     */
    inline char getID() const{ return id;}

    /** Kiszámítja a havi Forgalom és a Díjcsomag alapján, hogy mennyit kell fizetnie az Ügyfélnek
     * @param forg A havi Forgalom referenciája.
     * @return A havidíj értéke egy Ügyfélnek a csomagban.
     */
    virtual inline size_t dijkalkulator(const Forgalom& forg) const{
        size_t sum = (forg.getSMS() * smsdij) + (forg.getPerc() * percdij);
        return sum;
    }

    /// Virtuális destruktor
    virtual ~Alap() = default;
};

/// SMSMax díjcsomagosztály, amely egy bizonyos mennyiségű ingyen sms-t ad egy adott hónapban
class SMSMax :public Alap{
    size_t freesms;     ///< Ingyen küldhető SMS-ek száma
public:
    /** Konstruktor
     * @param id Díjcsomag azonosító referenciája.
     * @param sms Az SMS díj értéke a csomagban.
     * @param perc A Percdíj értéke a csomagban.
     * @param db Ingyen küldhető SMS-ek száma a csomagban.
     */
    inline explicit SMSMax(const char& id = 'S', size_t sms = 30, size_t perc = 30, size_t db = 50)
            :Alap(id, sms, perc), freesms(db) {}

    /** Dijkalkulátor átdefiniálása
     * @param forg A havi Forgalom referenciája.
     * @return A havidíj értéke egy Ügyfélnek a csomagban.
     */
    inline size_t dijkalkulator(const Forgalom& forg) const override{
        size_t sum = 0;
        if (((int)forg.getSMS() - (int)freesms) >= 0)
            sum = forg.getSMS() - freesms;
        sum = (sum * smsdij) + (forg.getPerc() * percdij);
        return sum;
    }
};

/// MobilNet díjcsomagosztály, amelyben van egy mobilinternet alapdíj
class MobilNet :public Alap{
    size_t mobilinternet;   ///< Alapdíja a díjcsomagnak
public:
    /** Konstruktor
     * @param id Díjcsomag azonosító referenciája.
     * @param sms Az SMS díj értéke a csomagban.
     * @param perc A Percdíj értéke a csomagban.
     * @param mint Az alapdíja a csomagnak.
     */
    inline explicit MobilNet(const char& id = 'M', size_t sms = 60, size_t perc = 40, size_t mint = 1500)
            :Alap(id, sms, perc), mobilinternet(mint) {}

    /** Dijkalkulátor átdefiniálása
     * @param forg A havi Forgalom referenciája.
     * @return A havidíj értéke egy Ügyfélnek a csomagban.
     */
    inline size_t dijkalkulator(const Forgalom& forg) const override{
        size_t sum = mobilinternet + (forg.getSMS() * smsdij) + (forg.getPerc() * percdij);
        return sum;
    }
};

#endif //MOBILSZOL_DIJCSOMAGOK_H
