
#include "Parser.hpp"

#include <iostream>
#include <string>

int main()
{
    std::cout << "Modern C++ Calculator\n";
    std::cout << "Type 'exit' to quit\n\n";
    std::cout << "Enter mathmatical expression\n";

    while (true)
    {
        try
        {
            std::cout << "> ";

            std::string input;
            std::getline(std::cin, input);

            if (input == "exit")
            {
                break;
            }

            if (input.empty())
            {
                continue;
            }

            Tokenizer tokenizer(input);

            Parser parser(tokenizer);

            double result = parser.parse();

            std::cout << result << "\n";
        }
        catch (const std::exception& ex)
        {
            std::cout << "Error: "
                      << ex.what()
                      << "\n";
        }
    }

    return 0;
}