
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


/**
 * @brief Handles user input and translates full sentences.
 */
class TranslationApp
{
private:
    MorseTranslator translator;

    /**
     * @brief Translates each English letter in a sentence.
     * @param sentence The sentence entered by the user.
     * @return Nothing.
     */
    void translateSentence(const char sentence[])
    {
        bool printedLetter = false;

        // Go through the sentence one character at a time.
        for (int i = 0; sentence[i] != '\0'; i++)
        {
            const char* morse =
                translator.getMorseCode(sentence[i]);

            // Skip spaces, numbers, and punctuation.
            if (morse[0] != '\0')
            {
                // Separate Morse symbols with a space.
                if (printedLetter)
                {
                    cout << " ";
                }

                cout << morse;
                printedLetter = true;
            }
        }

        if (!printedLetter)
        {
            cout << "(No English letters found)";
        }

        cout << endl;
    }

public:
    /**
     * @brief Gets a sentence and displays its Morse code.
     * @return Nothing.
     */
    void runOnce()
    {
        char sentence[52];

        cout << "Enter a sentence (max 50 characters): ";
        cin.getline(sentence, 52);

        // Reject input that's longer than 50 characters.
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Please enter 50 characters or less."
                 << endl;
            return;
        }

        cout << "\nMorse Code:" << endl;
        translateSentence(sentence);
    }
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
    // Start the application and translate one sentence.
    TranslationApp app;
    app.runOnce();

    return 0;
}
