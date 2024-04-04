/*
 * Advent of code day 1
 */

#include <vector>
#include <string>
#include <iostream>
#include <string.h>
#include "readfile.hpp"

struct Digit2WordList_T
{
    unsigned int digit;
    const char  *word;
};

const Digit2WordList_T arr[10] = {
        {1, "one"},
        {2, "two"},
        {3, "three"},
        {4, "four"},
        {5, "five"},
        {6, "six"},
        {7, "seven"},
        {8, "eight"},
        {9, "nine"},
        {-1U, NULL}
};

unsigned int
findFirstNum(const string line)
{
    for(unsigned int i = 0; i < strlen(line.c_str()); i++)
        if(isdigit(line[i]))
            return line[i] - '0';

    return -1U;
}

unsigned int
findLastNum(const string line)
{
    for(unsigned int i = strlen(line.c_str()) - 1; i != -1; i--)
        if(isdigit(line[i]))
            return line[i] - '0';

    return -1U;
}

unsigned int
findCalibrationValues_Digits(vector<string>* input)
{
    vector<string>::iterator line_iter;
    unsigned int first_num, last_num, line_num, sum;

    sum = line_num = 0;
    for(line_iter = input->begin(); line_iter != input->end(); line_iter++, line_num++)
    {
        first_num = last_num = -1U;
        first_num = findFirstNum(*line_iter);
        last_num  = findLastNum(*line_iter);

        if(first_num == -1U)
        {
            printf("ERROR: No first number found as calibration value in line %d\n", line_num + 1);
            return -1U;
        }

        if(last_num  == -1U)
        {
            printf("ERROR: No last number found as calibration value in line %d\n", line_num + 1);
            return -1U;
        }

        sum += 10 * first_num + last_num;
    }

    return sum;
}

unsigned int
findFirst(const string line)
{
    unsigned int digit_pos, word_pos, word_val;
    const char* pos_curr;

    digit_pos = -1U;
    for(unsigned int i = 0; i < strlen(line.c_str()); i++)
    {
        if(isdigit(line[i]))
        {
            digit_pos = i;
            break;
        }
    }

    if(digit_pos == 0)
        return line[digit_pos] - '0';

    word_val = word_pos = -1U;
    for(unsigned int i = 0; arr[i].digit != -1U; i++)
    {
        if((pos_curr = strstr(&line[0], arr[i].word)) != NULL)
        {
            if(word_pos == -1U)
            {
                word_val = arr[i].digit;
                word_pos = pos_curr - &line[0];
            }
            else
            {
                if(pos_curr - &line[0] < word_pos)
                {
                    word_val = arr[i].digit;
                    word_pos = pos_curr - &line[0];
                }
            }
        }
    }

    if(digit_pos == -1U &&
       word_pos  == -1U)
        return -1U;

    if(digit_pos < word_pos ||
       word_pos == -1U)
        return line[digit_pos] - '0';

    return word_val;
}

unsigned int
findLast(const string line)
{
    unsigned int digit_pos, word_pos, word_val, line_len;
    const char  *pos_last;

    line_len = strlen(line.c_str());
    pos_last = &line[line_len - 1];

    digit_pos = -1U;
    for(unsigned int i = line_len - 1; i != -1; i--)
    {
        if(isdigit(line[i]))
        {
            digit_pos = i;
            break;
        }
    }

    if(digit_pos == line_len - 1)
        return line[digit_pos] - '0';

    word_pos = word_val = -1U;
    for(unsigned int i = line_len - 1; i != -1; i--)
    {
        for(unsigned int j = 0; arr[j].word != NULL; j++)
        {
            if(strstr(&line[i], arr[j].word) != NULL)
            {
                word_val = arr[j].digit;
                word_pos = i;
                break;
            }
        }

        if(word_val != -1U)
            break;
    }

    if(digit_pos == -1U &&
       word_pos  == -1U)
        return -1U;

    if(digit_pos > word_pos ||
       word_pos == -1U)
        return line[digit_pos] - '0';

    return word_val;
}

unsigned int
findCalibrationValues(vector<string>* input)
{
    vector<string>::iterator line_iter;
    unsigned int first_num, last_num, line_num, sum;

    sum = line_num = 0;
    for(line_iter = input->begin(); line_iter != input->end(); line_iter++, line_num++)
    {
        first_num = last_num = -1U;
        first_num = findFirst(*line_iter);
        last_num  = findLast(*line_iter);

        if(first_num == -1U)
        {
            printf("ERROR: No first word found as calibration value in line %d\n", line_num + 1);
            return -1U;
        }

        if(last_num  == -1U)
        {
            printf("ERROR: No last word found as calibration value in line %d\n", line_num + 1);
            return -1U;
        }

        sum += 10 * first_num + last_num;
    }

    return sum;
}

int main()
{
    FileReader Input("input_01.txt");
    Input.ReadFile();

    vector<string> Input_Ctnt = Input.getFileContent();

    unsigned int CalibrationValuesSum1 = 0;
    unsigned int CalibrationValuesSum2 = 0;

    CalibrationValuesSum1 = findCalibrationValues_Digits(&Input_Ctnt);

    printf("Sum of calibration values (part one): %d\n", CalibrationValuesSum1);

    CalibrationValuesSum2 = findCalibrationValues(&Input_Ctnt);

    printf("Sum of calibration values (part two): %d\n", CalibrationValuesSum2);

    return 0;
}
