
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
                // Convert the array position back into a letter.
                return static_cast<char>('A' + i);
            }
        }

        // Return an empty character if nothing matches.
        return '\0';
    }
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

            // Use a slash to separate words in Morse code.
            if (sentence[i] == ' ')
            {
                if (printedLetter)
                {
                    cout << " /";
                }

                continue;
            }

            const char *morse =
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

    /**
     * @brief Translates a full Morse code sentence into English.
     * @param sentence The Morse code entered by the user.
     * @return Nothing.
     */
    void translateMorseSentence(const char sentence[])
    {
        char currentCode[501];
        int codeLength = 0;
        bool printedSomething = false;

        // Go through the Morse code one character at a time.
        for (int i = 0;; i++)
        {
            char symbol = sentence[i];

            // Build one Morse code pattern.
            if (symbol != ' ' && symbol != '/' && symbol != '\0')
            {
                currentCode[codeLength] = symbol;
                codeLength++;
            }
            else
            {
                // Translate the pattern when we reach a separator.
                if (codeLength > 0)
                {
                    currentCode[codeLength] = '\0';

                    char letter = translator.getEnglishLetter(currentCode);

                    // Show a question mark for unknown Morse patterns.
                    if (letter == '\0')
                    {
                        cout << "?";
                    }
                    else
                    {
                        cout << letter;
                    }

                    codeLength = 0;
                    printedSomething = true;
                }

                // A slash represents a space between words.
                if (symbol == '/')
                {
                    cout << " ";
                    printedSomething = true;
                }

                // Stop when we reach the end of the sentence.
                if (symbol == '\0')
                {
                    break;
                }
            }
        }

        if (!printedSomething)
        {
            cout << "(No Morse code entered)";
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

        // Handle input that's too long for our array.
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Please enter 50 characters or less."
                 << endl;
            return;
        }

        // Check the actual length, including spaces.
        if (strlen(sentence) > 50)
        {
            cout << "Please enter 50 characters or less."
                 << endl;
            return;
        }

        // Don't translate an empty sentence.
        if (sentence[0] == '\0')
        {
            cout << "Please enter a sentence." << endl;
            return;
        }

        cout << "\nMorse Code:" << endl;
        translateSentence(sentence);
    }

    /**
     * @brief Gets Morse code from the user and translates it.
     * @return Nothing.
     */
    void runMorseToEnglish()
    {
        char morseSentence[501];

        cout << "Enter Morse code (use spaces between letters "
             << "and / between words): ";
        cin.getline(morseSentence, 501);

        // Handle input that's too long.
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Morse code input is too long." << endl;
            return;
        }

        // Don't translate empty input.
        if (morseSentence[0] == '\0')
        {
            cout << "Please enter some Morse code." << endl;
            return;
        }

        cout << "\nEnglish:" << endl;
        translateMorseSentence(morseSentence);
    }

    /**
     * @brief Displays the translation menu until the user quits.
     * @return Nothing.
     */
    void run()
    {
        int choice = 0;

        // Keep showing the menu until the user chooses Quit.
        while (choice != 3)
        {
            cout << "\n=== Morse Code Translator ===" << endl;
            cout << "1. English to Morse" << endl;
            cout << "2. Morse to English" << endl;
            cout << "3. Quit" << endl;
            cout << "\nSelect an option: ";

            cin >> choice;

            // Handle letters or other non-number menu input.
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

            // Remove the newline before using getline().
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
                cout << "Thanks for using the Morse Code Translator!"
                     << endl;
            }
            else
            {
                cout << "Please enter 1, 2, or 3." << endl;
            }
        }
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
    app.run();

    return 0;
}
