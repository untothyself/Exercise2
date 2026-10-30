
/**
 * @file Lab1_Ahassan124.cpp
 * @author Abass Hassan
 * @date 2026-10-30
 * @brief Translates English sentences into Morse code.
 *        Also supports Morse to English translation.
 */

#include <iostream>
#include <cctype> // For toupper()
using namespace std;

/**
 * @brief Handles translating English letters into Morse code.
 */
class MorseTranslator
{
private:
    // Morse code for A through Z, in alphabetical order.
    const char *morseCodes[26] = {
        ".-",   // A
        "-...", // B
        "-.-.", // C
        "-..",  // D
        ".",    // E
        "..-.", // F
        "--.",  // G
        "....", // H
        "..",   // I
        ".---", // J
        "-.-",  // K
        ".-..", // L
        "--",   // M
        "-.",   // N
        "---",  // O
        ".--.", // P
        "--.-", // Q
        ".-.",  // R
        "...",  // S
        "-",    // T
        "..-",  // U
        "...-", // V
        ".--",  // W
        "-..-", // X
        "-.--", // Y
        "--.."  // Z
    };

public:
    /**
     * @brief Finds the Morse code for an English letter.
     * @param letter The character we want to translate.
     * @return The Morse code, or an empty string for invalid characters.
     */
    const char *getMorseCode(char letter) const
    {
        // Make lowercase letters uppercase before looking them up.
        if (letter >= 'a' && letter <= 'z')
        {
            letter = toupper(letter);
        }

        // Skip anything that isn't an English letter.
        if (letter < 'A' || letter > 'Z')
        {
            return "";
        }

        // Find the matching Morse code using the letter's position.
        return morseCodes[letter - 'A'];
    }
};

/**
 * @brief Starts the Morse code translation program.
 * @return 0 if the program finishes successfully.
 */
int main()
{
    // Create our translator and few letters.
    MorseTranslator translator;

    cout << "A: " << translator.getMorseCode('A') << endl;
    cout << "b: " << translator.getMorseCode('b') << endl;
    cout << "Z: " << translator.getMorseCode('Z') << endl;

    return 0;
}
