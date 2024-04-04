/*
 * Advent of code day 2
 */

#include <cstring>
#include "readfile.hpp"

struct CubesT
{
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};

const CubesT ElfCubes = {
        12,
        13,
        14
};

unsigned int
getNumber(const char* colour_start)
{
    unsigned int space_counter = 0;

    for(;; colour_start--)
    {
        if(*colour_start == ' ')
            space_counter++;

        if(space_counter == 2)
            break;
    }

    return atoi(colour_start);
}

CubesT
getColours(const char* set)
{
    const char *pos_r, *pos_g, *pos_b;
    CubesT set_colours;

    if((pos_r = strstr(set, "red")) != NULL)
        set_colours.red = getNumber(pos_r);
    else
        set_colours.red = 0;

    if((pos_g = strstr(set, "green")) != NULL)
        set_colours.green = getNumber(pos_g);
    else
        set_colours.green = 0;

    if((pos_b = strstr(set, "blue")) != NULL)
        set_colours.blue = getNumber(pos_b);
    else
        set_colours.blue = 0;

    return set_colours;
}

unsigned int
parseLineGameSum(const string line)
{
    unsigned int line_len, game_num, semicolon_pos, set_num, prev_pos;
    bool isPossible = true;

    line_len = strlen(line.c_str());
    game_num = atoi(&line[5]);

    set_num = 1;
    for(unsigned int i = 0; i < line_len; i++)
    {
        if(line[i] == ';')
            set_num++;

        if(line[i] == ':')
            semicolon_pos = i;
    }

    CubesT LineSet[set_num];

    prev_pos = semicolon_pos;
    if(set_num > 1)
    {
        unsigned int index = 0;

        for(unsigned int i = semicolon_pos; i < line_len; i++)
        {
            char buffer[50];

            if(line[i] == ';' ||
               i == line_len - 1)
            {
                strncpy(buffer, &line[prev_pos + 1], i - prev_pos - 1);
                buffer[i - prev_pos - 1] = '\0';
                LineSet[index++] = getColours(buffer);
                prev_pos = i;
            }
        }
    }
    else
        LineSet[0] = getColours(&line[semicolon_pos]);

    // Loop over sets
    for(unsigned int i = 0; i < set_num; i++)
    {
        if(LineSet[i].red   > ElfCubes.red   ||
           LineSet[i].green > ElfCubes.green ||
           LineSet[i].blue  > ElfCubes.blue)
        {
            isPossible = false;
            break;
        }
    }

    if(isPossible)
        return game_num;

    return 0;
}

unsigned int
parseGames(vector<string>* input)
{
    vector<string>::iterator line_iter;
    unsigned int line_num, sum;

    line_num = sum = 0;
    for(line_iter = input->begin(); line_iter != input->end(); line_iter++, line_num++)
        sum += parseLineGameSum(*line_iter);

    return sum;
}

unsigned int
parseLinePowerSum(const string line)
{
    unsigned int line_len, game_num, semicolon_pos, set_num, prev_pos;
    unsigned int min_r, min_g, min_b;

    line_len = strlen(line.c_str());
    game_num = atoi(&line[5]);

    set_num = 1;
    for(unsigned int i = 0; i < line_len; i++)
    {
        if(line[i] == ';')
            set_num++;

        if(line[i] == ':')
            semicolon_pos = i;
    }

    CubesT LineSet[set_num];

    prev_pos = semicolon_pos;
    if(set_num > 1)
    {
        unsigned int index = 0;

        for(unsigned int i = semicolon_pos; i < line_len; i++)
        {
            char buffer[50];

            if(line[i] == ';' ||
               i == line_len - 1)
            {
                strncpy(buffer, &line[prev_pos + 1], i - prev_pos - 1);
                buffer[i - prev_pos - 1] = '\0';
                LineSet[index++] = getColours(buffer);
                prev_pos = i;
            }
        }
    }
    else
        LineSet[0] = getColours(&line[semicolon_pos]);

    min_r = min_g = min_b = 0;
    for(unsigned int i = 0; i < set_num; i++)
    {
        if(min_r == 0)
            min_r = LineSet[i].red;

        if(min_g == 0)
            min_g = LineSet[i].green;

        if(min_b == 0)
            min_b = LineSet[i].blue;

        if(min_r < LineSet[i].red &&
           min_r != 0)
            min_r = LineSet[i].red;

        if(min_g < LineSet[i].green &&
           min_g != 0)
            min_g = LineSet[i].green;

        if(min_b < LineSet[i].blue &&
           min_b != 0)
            min_b = LineSet[i].blue;
    }

    return min_r * min_g * min_b;
}

unsigned int
parsePowers(vector<string>* input)
{
    vector<string>::iterator line_iter;
    unsigned int line_num, sum;

    line_num = sum = 0;
    for(line_iter = input->begin(); line_iter != input->end(); line_iter++, line_num++)
        sum += parseLinePowerSum(*line_iter);

    return sum;
}

int main()
{
    FileReader Input("input_02.txt");
    Input.ReadFile();

    vector<string> Input_Ctnt = Input.getFileContent();

    unsigned int GameSum = 0, PowerSum = 0;

    GameSum = parseGames(&Input_Ctnt);

    printf("Sum of possible games: %d\n", GameSum);

    PowerSum = parsePowers(&Input_Ctnt);

    printf("Sum of powers: %d\n", PowerSum);

    return 0;
}
