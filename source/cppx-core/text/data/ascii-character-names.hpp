#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

namespace cppx
{
    namespace ascii
    {
        const char      null        = '\0';         // '\0' 0x00
        const char      bell        = '\a';         // '\a' 0x07, ^G
        const char      backspace   = '\b';         // '\b' 0x07, ^H
        const char      tab         = '\t';         // '\t' 0x08, ^I, horizontal tab
        const char      linefeed    = '\n';         // '\n' 0x09, ^J
        const char      vtab        = '\v';         // '\v' 0x0A, ^K
        const char      formfeed    = '\f';         // '\f' 0x0B, ^L
        const char      enter       = '\r';         // '\r' 0x0C, ^M
        const char      xon         = '\x11';       //      0x11, ^Q, "continue"
        const char      xoff        = '\x13';       //      0x13, ^S, "stop"
        const char      end_of_text = '\x1A';       //      0x1A, ^Z, non-std MS meaning.
        const char      escape      = '\x1B';       //      0x1B
        const char      space       = ' ';          //      0x20
        const char      del         = '\x7F';       //      0x7F

        const char      first_char  = char( 0 );    static_assert( first_char == null );
        const char      last_char   = char( 127 );  static_assert( last_char == del );

        // Standard but unfortunately uppercase abbreviations as per ASCII '67:
        const char      NUL         = null;
        const char      BEL         = bell;
        const char      BS          = backspace;
        const char      HT          = tab;          // “Horizontal tab”
        const char      LF          = linefeed;
        const char      VT          = vtab;         // “Vertical tab”
        const char      FF          = formfeed;
        const char      CR          = enter;        // “Carriage return”
        const char      DC1         = xon;          // “Device control 1”
        const char      DC3         = xoff;         // “Device control 3”
        const char      SUB         = end_of_text;  // “Substitute”, but see below!
        const char      ESC         = escape;
        const char      SPC         = space;
        const char      DEL         = del;          // “Delete”

        // ASCII DEL, code 0x7F = 127, “delete”, can be used as a replacement for encoding
        // errors or unrepresentable code point.
        //
        // ASCII has a character dedicated to the purpose: SUB “substitute”, code 26,
        // ^Z. But in Windows ^Z is used as an EOF marker for text streams. So ^Z as
        // replacement is not usable in Windows, i.e. it's not a general solution.
        //
        // Unicode, an extension of ASCII, also has its own character dedicated to
        // the purpose, namely code U+FFFD “replacement character”. It translates to
        // at least two UTF-8 bytes so it's not trivial to check for. And it can't be
        // represented in simple single byte encodings such as codepage 437, so it's
        // not usable in single byte encodings, i.e. it's not a general solution.
        //
        // Using ASCII DEL as a replacement character does not preclude using it also to
        // represent the DEL key in a keyboard interface, for in that context there is no
        // possibility of encoding errors or unrepresentable code point. It doesn't appear
        // in ordinary text. And it even has some mnemonic value as a deleted character.
        //
        // For these reasons I recommend using ASCII DEL as replacement and error
        // indication character:

        const char      bad_char    = del;

    }  // namespace ascii

    const char      std_ascii_bad_char      = ascii::end_of_text;
    const wchar_t   std_unicode_bad_char    = L'\uFFFD';

}  // namespace cppx
