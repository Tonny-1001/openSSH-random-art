#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

string hexToBits(string hex)
{
    string bits;
    for (int i = 0; i < hex.length(); i++)
    {
        if (hex[i] == '0')
        {
            bits += "0000";
        }
        else if (hex[i] == '1')
        {
            bits += "0001";
        }
        else if (hex[i] == '2')
        {
            bits += "0010";
        }
        else if (hex[i] == '3')
        {
            bits += "0011";
        }
        else if (hex[i] == '4')
        {
            bits += "0100";
        }
        else if (hex[i] == '5')
        {
            bits += "0101";
        }
        else if (hex[i] == '6')
        {
            bits += "0110";
        }
        else if (hex[i] == '7')
        {
            bits += "0111";
        }
        else if (hex[i] == '8')
        {
            bits += "1000";
        }
        else if (hex[i] == '9')
        {
            bits += "1001";
        }
        else if (hex[i] == 'a' || hex[i] == 'A')
        {
            bits += "1010";
        }
        else if (hex[i] == 'b' || hex[i] == 'B')
        {
            bits += "1011";
        }
        else if (hex[i] == 'c' || hex[i] == 'C')
        {
            bits += "1100";
        }
        else if (hex[i] == 'd' || hex[i] == 'D')
        {
            bits += "1101";
        }
        else if (hex[i] == 'e' || hex[i] == 'E')
        {
            bits += "1110";
        }
        else if (hex[i] == 'f' || hex[i] == 'F')
        {
            bits += "1111";
        }
        else
        {
            cout << "unknown char: " << hex[i];
            exit(1);
        }
    }
    return bits;
};

void printRandomArt(
    int endX, 
    int endY, 
    int startX, 
    int startY, 
    int rows, 
    int cols, 
    vector<vector<int>> grid
){
    vector<char> chars = {' ', '.', 'o', '+', '=', '*', 'B', 'O', 'X', '@', '%', '&', '#', '/', '^'};
    string final_art = "";
    final_art = final_art + "+" + string(cols, '-') + "+\n";
    for (int i = 0; i < rows; i++)
    {
        final_art += "|";
        for (int j = 0; j < cols; j++)
        {
            if (startX == j && startY == i)
            {
                final_art += "S";
            }
            else if (j == endX && i == endY)
            {
                final_art += "E";
            }
            else
            {
                char selected_char;
                if (grid[i][j] > chars.size())
                {
                    selected_char = chars[chars.size() - 1];
                }
                else
                {
                    selected_char = chars[grid[i][j]];
                }
                final_art += selected_char;
            }
        }
        final_art += "|";
        final_art += "\n";
    }
    final_art = final_art + "+" + string(cols, '-') + "+\n";

    cout << final_art;
}

int main()
{
    const int rows = 9;
    const int cols = 17;
    string my_hash; // hex hash format

    cin >> my_hash;

    const string hash_bits = hexToBits(my_hash);
    // cout << hash_bits << "\n";

    // create 2d table
    vector<vector<int>> grid(rows, vector<int>(cols, 0));

    // parsing bits
    int xPos = cols / 2;
    int yPos = rows / 2;
    int startX = xPos;
    int startY = yPos;
    for (int i = 8; i <= hash_bits.length(); i += 8)
    {
        for (int j = i - 2; j >= i - 8; j -= 2)
        {
            string bitPair = hash_bits.substr(j, 2);

            // cout << xPos << ", " << yPos << "\n";
            // cout << bitPair << ", " << i << ", " << j << "\n";

            if (bitPair == "00")
            {
                xPos--;
                yPos--;
            }
            else if (bitPair == "01")
            {
                xPos++;
                yPos--;
            }
            else if (bitPair == "10")
            {
                xPos--;
                yPos++;
            }
            else if (bitPair == "11")
            {
                xPos++;
                yPos++;
            }

            // block the posibilyty of going out of the grid boundries
            yPos = max(0, min(yPos, rows - 1));
            xPos = max(0, min(xPos, cols - 1));
            grid[yPos][xPos]++;
        }
    }

    printRandomArt(xPos, yPos, startX, startY, rows, cols, grid);

    return 0;
};
