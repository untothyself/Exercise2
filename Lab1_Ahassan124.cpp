/**
 * @file Lab1_Ahassan124.cpp
 * @author Abass Hassan
 * @date 2026-10-30
 * @brief Translates English sentences into Morse code and Morse code into English.
 */

#include <iostream>
#include <cctype>  // For toupper()
#include <cstring> // For strlen() and strcmp()
using namespace std;

/**
 * @brief Handles looking up English letters and their Morse code patterns.
 */
class MorseTranslator
{
private:
    // Morse code for A through Z, in alphabetical order.
    const char* morseCodes[26] = {
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
    const char* getMorseCode(char letter) const
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

    /**
     * @brief Finds the English letter for a Morse code pattern.
     * @param morse The Morse code pattern to look up.
     * @return The matching English letter, or '\0' if not found.
     */
    char getEnglishLetter(const char morse[]) const
    {
        // Check each Morse code pattern in our array.
        for (int i = 0; i < 26; i++)
        {
            // strcmp returns 0 when both strings match.
            if (strcmp(morse, morseCodes[i]) == 0)
            {
                return static_cast<char>('A' + i);
            }
        }

        return '\0';
    }
};

/**
 * @brief Handles user input and translating full sentences in either direction.
 */
class TranslationApp
{
private:
    MorseTranslator translator;

    /**
     * @brief Translates each English letter in a sentence into Morse code.
     * @param sentence The sentence entered by the user.
     * @return Nothing.
     */
    void translateSentence(const char sentence[])
    {
        bool printedLetter = false;
        bool pendingWordSpace = false;

        // Go through the sentence one character at a time.
        for (int i = 0; sentence[i] != '\0'; i++)
        {
            // Remember a word break, but don't print it unless another letter follows.
            if (sentence[i] == ' ')
            {
                if (printedLetter)
                {
                    pendingWordSpace = true;
                }
                continue;
            }

            const char* morse = translator.getMorseCode(sentence[i]);

            // Skip numbers and punctuation.
            if (morse[0] != '\0')
            {
                if (printedLetter)
                {
                    if (pendingWordSpace)
                    {
                        cout << " / ";
                    }
                    else
                    {
                        cout << " ";
                    }
                }

                cout << morse;
                printedLetter = true;
                pendingWordSpace = false;
            }
        }

        if (!printedLetter)
        {
            cout << "(No English letters found)";
        }

        cout << endl;
    }

    /**
     * @brief Translates a full Morse code sentence into English.
     * @param sentence The Morse code entered by the user.
     * @return Nothing.
     */
    void translateMorseSentence(const char sentence[])
    {
        char currentCode[501];
        int codeLength = 0;
        bool printedLetter = false;
        bool pendingWordSpace = false;

        // Read one Morse pattern at a time, separated by spaces or a slash.
        for (int i = 0; ; i++)
        {
            char symbol = sentence[i];

            if (symbol != ' ' && symbol != '/' && symbol != '\0')
            {
                currentCode[codeLength] = symbol;
                codeLength++;
            }
            else
            {
                if (codeLength > 0)
                {
                    currentCode[codeLength] = '\0';
                    char letter = translator.getEnglishLetter(currentCode);

                    // Print just one space between words, not at the ends.
                    if (printedLetter && pendingWordSpace)
                    {
                        cout << " ";
                    }

                    // Use a question mark if the pattern isn't an English letter.
                    if (letter == '\0')
                    {
                        cout << "?";
                    }
                    else
                    {
                        cout << letter;
                    }

                    printedLetter = true;
                    pendingWordSpace = false;
                    codeLength = 0;
                }

                // A slash marks the break between two words.
                if (symbol == '/' && printedLetter)
                {
                    pendingWordSpace = true;
                }

                if (symbol == '\0')
                {
                    break;
                }
            }
        }

        if (!printedLetter)
        {
            cout << "(No Morse code entered)";
        }

        cout << endl;
    }

public:
    /**
     * @brief Gets one English sentence and displays its Morse code.
     * @return Nothing.
     */
    void runOnce()
    {
        char sentence[52];

        cout << "Enter a sentence (max 50 characters): ";
        cin.getline(sentence, 52);

        // Clear the input if the sentence is too long.
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Please enter 50 characters or less." << endl;
            return;
        }

        // A 51-character sentence fits the array but is still too long.
        if (strlen(sentence) > 50)
        {
            cout << "Please enter 50 characters or less." << endl;
            return;
        }

        if (sentence[0] == '\0')
        {
            cout << "Please enter a sentence." << endl;
            return;
        }

        cout << "\nMorse Code:" << endl;
        translateSentence(sentence);
    }

    /**
     * @brief Gets Morse code from the user and translates it into English.
     * @return Nothing.
     */
    void runMorseToEnglish()
    {
        char morseSentence[501];

        cout << "Enter Morse code (use spaces between letters "
             << "and / between words): ";
        cin.getline(morseSentence, 501);

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Morse code input is too long." << endl;
            return;
        }

        if (morseSentence[0] == '\0')
        {
            cout << "Please enter some Morse code." << endl;
            return;
        }

        cout << "\nEnglish:" << endl;
        translateMorseSentence(morseSentence);
    }

    /**
     * @brief Displays the translation menu until the user chooses Quit.
     * @return Nothing.
     */
    void run()
    {
        int choice = 0;

        while (choice != 3)
        {
            cout << "\n=== Morse Code Translator ===" << endl;
            cout << "1. English to Morse" << endl;
            cout << "2. Morse to English" << endl;
            cout << "3. Quit" << endl;
            cout << "\nSelect an option: ";

            cin >> choice;

            // Clear invalid menu input and ask again.
            if (cin.fail())
            {
                if (cin.eof())
                {
                    break;
                }

                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Please enter 1, 2, or 3." << endl;
                continue;
            }

            // Remove the newline before the next getline().
            cin.ignore(10000, '\n');

            if (choice == 1)
            {
                runOnce();
            }
            else if (choice == 2)
            {
                runMorseToEnglish();
            }
            else if (choice == 3)
            {
                cout << "Thanks for using the Morse Code Translator!" << endl;
            }
            else
            {
                cout << "Please enter 1, 2, or 3." << endl;
            }
        }
    }
};

/**
 * @brief Starts the Morse code translator.
 * @return 0 if the program finishes successfully.
 */
int main()
{
    TranslationApp app;
    app.run();

    return 0;
}
