#ifndef STRING_H
#define STRING_H

/**
 * A String osztály.
 * A 'pData'-ban vannak a karakterek (a lezáró nullával együtt), 'len' a hossza.
 * A hosszba nem számít bele a lezáró nulla.
 */
class String {
    char *pData;        ///< Pointer a sztringre
    size_t len;         ///< Hossz lezáró nulla nélkül
public:
    /** Konstruktor
     * @param s A tárolandó Stringre mutató pointer.
     */
    explicit String(char const* s = "");

    /** C-sztringre mutató pointert ad vissza
     * @return A String értékére mutató pointer.
     */
    inline const char* c_str() const { return pData;}

    /** Másoló konstruktor
     * @param copy A lemásolandó String referenciája.
     */
    String(String const& copy);

    /** Értékadó operator
     * @param rhs A lemásolandó String referenciája.
     * @return A lemásolt String referenciája (láncolhatóság miatt).
     */
    String& operator=(String const& rhs);

    /** Egyenlőség operator
     * @param rhs Az egyenlőség vizsgálat jobb oldalán álló String referenciája.
     * @return Egyenlő-e? (bool)
     */
    bool operator==(const String& rhs) const;

    /** Egyenlőtlenség operator
     * @param rhs Az egyenlőtlenség vizsgálat jobb oldalán álló String referenciája.
     * @return Egyenlőtlen-e? (bool)
     */
    bool operator!=(const String& rhs) const;

    /** Sztringhez karaktert fűz
     * @param s A Stringhez fűzendő karakter referenciája.
     * @return A String értéke.
     */
    String operator+(const char& s) const;

    /** Összefűzés Stringet Stringgel
     * @param s A Stringhez fűzendő String referenciája.
     * @return A String értéke.
     */
    String operator+(String const& s) const;

    /// Destruktor
    inline ~String() { delete[] pData;}
};

/** Kiíró operator
 * @param os A kiíró stream referenciája.
 * @param str A kiírandó String referenciája.
 * @return A kiíró stream referenciája (láncolhatóság miatt).
 */
std::ostream& operator<<(std::ostream& os, String const& str);

/** Beolvasó operator, ami eldobja a felesleges whitespacet a szöveg elejéről és space után megáll
 * @param is A beolvasó stream referenciája.
 * @param s0 A beolvasandó String referenciája.
 * @return A beolvasó stream referenciája (láncolhatóság miatt).
 */
std::istream& operator>>(std::istream& is, String& s0);

#endif
