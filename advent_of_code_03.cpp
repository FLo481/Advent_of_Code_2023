/*
 * Advent of code day 3
 */

#include <string.h>
#include "readfile.hpp"

bool
isPartNumber(const string line,
             unsigned int start_pos,
             unsigned int end_pos)
{
    unsigned int start, end;

    if(start_pos != 0)
        start = start_pos - 1;
    else
        start = start_pos;

    if(end_pos != strlen(line.c_str()) - 1)
        end = end_pos + 1;
    else
        end = end_pos;

    for(unsigned int i = start; i <= end; i++)
        if(!isdigit(line[i]) && line[i] != '.')
            return true;

    return false;
}

unsigned int
findStartofNumber(const string line,
                  unsigned int curr_pos)
{
    for(unsigned int start = curr_pos; start != -1; start--)
    {
        if(start == 0 &&
           isdigit(line[start]))
            return start;

        if(!isdigit(line[start]))
            return start + 1;
    }

    return -1U;
}

unsigned int
getGearRatio(const string line,
             unsigned int pos)
{
    unsigned int start, end, start_pos;

    if(pos != 0)
        start = pos - 1;
    else
        start = pos;

    if(pos != strlen(line.c_str()) - 1)
        end = pos + 1;
    else
        end = pos;

    for(unsigned int i = start; i <= end; i++)
    {
        if(isdigit(line[i]))
        {
            start_pos = findStartofNumber(line, i);
            return atoi(&line[start_pos]);
        }
    }

    return 0;
}

unsigned int
getEndofNumber(const string line,
               unsigned int line_len,
               unsigned int start_pos)
{
    unsigned int end_pos;

    for(end_pos = start_pos; end_pos < strlen(line.c_str()); end_pos++)
    {
        if(end_pos == line_len - 1)
            return line_len - 1;

        if(!isdigit(line[end_pos]))
            return end_pos - 1;
    }

    return -1U;
}

unsigned int
getPartNumbersInLine(const string prev_line,
                     const string line,
                     const string next_line,
                     unsigned int curr_line_num)
{
    unsigned int end_pos = -1U, sum = 0, line_len;

    line_len = strlen(line.c_str());

    for(unsigned int i = 0; i < line_len; i++)
    {
        if(line[i] == '.')
            continue;

        if(end_pos != -1U &&
           i <= end_pos)
            continue;

        if(isdigit(line[i]))
        {
            end_pos = getEndofNumber(line, line_len, i);

            // Check in front
            if(i > 0                 &&
               !isdigit(line[i - 1]) &&
               line[i - 1] != '.')
            {
                sum += atoi(&line[i]);
                continue;
            }

            // Check above
            if(strcmp(&prev_line[0], "\0") != 0 &&
               isPartNumber(prev_line, i, end_pos))
            {
                sum += atoi(&line[i]);
                continue;
            }

            // Check below
            if(strcmp(&next_line[0], "\0") != 0 &&
               isPartNumber(next_line, i, end_pos))
            {
                sum += atoi(&line[i]);
                continue;
            }

            // Check back
            if(end_pos < line_len - 1      &&
               !isdigit(line[end_pos + 1]) &&
               line[end_pos + 1] != '.')
            {
                sum += atoi(&line[i]);
                continue;
            }
        }
        else
            continue;
    }

    return sum;
}

unsigned int
parseLines4PartNumbers(vector<string>* input, unsigned int line_num)
{
    unsigned int sum = 0;

    for(unsigned int iter = 0; iter < line_num; iter++)
    {
        if(iter == 0)
        {
            sum += getPartNumbersInLine("\0", input->at(iter), input->at(iter + 1), iter);
        }
        else if(iter == line_num - 1)
        {
            sum += getPartNumbersInLine(input->at(iter - 1), input->at(iter), "\0", iter);
        }
        else
        {
            sum += getPartNumbersInLine(input->at(iter - 1), input->at(iter), input->at(iter + 1), iter);
        }
    }

    return sum;
}

unsigned int
getGearRatiosInLine(const string prev_line,
                    const string line,
                    const string next_line,
                    unsigned int curr_line_num)
{
    unsigned int sum = 0, line_len;

    line_len = strlen(line.c_str());

    for(unsigned int i = 0; i < line_len; i++)
    {
        if(line[i] == '*')
        {
            unsigned int rc_b, rc_a;

            // Check between
            if(i > 0                &&
               i < line_len - 1     &&
               isdigit(line[i - 1]) &&
               isdigit(line[i + 1]))
            {
                unsigned int start = findStartofNumber(line, i - 1);
                sum += atoi(&line[start]) * atoi(&line[i + 1]);
                continue;
            }

            // Check between above
            if(i > 0            &&
               i < line_len - 1 &&
               strcmp(&prev_line[0], "\0") != 0 &&
               isdigit(prev_line[i - 1])        &&
               isdigit(prev_line[i + 1])        &&
               !isdigit(prev_line[i]))
            {
                unsigned int start = findStartofNumber(prev_line, i - 1);
                sum += atoi(&prev_line[start]) * atoi(&prev_line[i + 1]);
                continue;
            }

            // Check between below
            if(i > 0            &&
               i < line_len - 1 &&
               strcmp(&next_line[0], "\0") != 0 &&
               isdigit(next_line[i - 1])        &&
               isdigit(next_line[i + 1])        &&
               !isdigit(next_line[i]))
            {
                unsigned int start = findStartofNumber(next_line, i - 1);
                sum += atoi(&next_line[start]) * atoi(&next_line[i + 1]);
                continue;
            }

            // Check same line and above
            //  Back (number in 'line' comes after asterisk)
            if(i > 0             &&
               i < line_len - 1  &&
               strcmp(&prev_line[0], "\0") != 0         &&
               (rc_a = getGearRatio(prev_line, i)) != 0 &&
               isdigit(line[i + 1])                     &&
               !isdigit(line[i - 1])
               )
            {
                sum += rc_a * atoi(&line[i + 1]);
                continue;
            }

            //  In front (number in 'line' comes before asterisk)
            if(i > 0             &&
               i < line_len - 1  &&
               strcmp(&prev_line[0], "\0") != 0         &&
               (rc_a = getGearRatio(prev_line, i)) != 0 &&
               isdigit(line[i - 1])                     &&
               !isdigit(line[i + 1]))
            {
                unsigned int start = findStartofNumber(line, i - 1);
                sum += rc_a * atoi(&line[start]);
                continue;
            }

            // Check same line and below
            //  Back
            if(i > 0             &&
               i < line_len - 1  &&
               strcmp(&next_line[0], "\0") != 0         &&
               (rc_b = getGearRatio(next_line, i)) != 0 &&
               isdigit(line[i + 1])                     &&
               !isdigit(line[i - 1]))
            {
                sum += rc_b * atoi(&line[i + 1]);
                continue;
            }

            //  In front
            if(i > 0             &&
               i < line_len - 1  &&
               strcmp(&next_line[0], "\0") != 0         &&
               (rc_b = getGearRatio(next_line, i)) != 0 &&
               isdigit(line[i - 1])                     &&
               !isdigit(line[i + 1]))
            {
                unsigned int start = findStartofNumber(line, i - 1);
                sum += rc_b * atoi(&line[start]);
                continue;
            }

            // Check diagonal
            if(strcmp(&prev_line[0], "\0") != 0 &&
               strcmp(&next_line[0], "\0") != 0 &&
               (rc_a = getGearRatio(prev_line, i)) != 0 &&
               (rc_b = getGearRatio(next_line, i)) != 0)
            {
                sum += rc_a * rc_b;
            }
        }
        else
            continue;
    }

    return sum;
}

unsigned int
parseLines4GearRatios(vector<string>* input, unsigned int line_num)
{
    unsigned int sum = 0;

    for(unsigned int iter = 0; iter < line_num; iter++)
    {
        if(iter == 0)
        {
            sum += getGearRatiosInLine("\0", input->at(iter), input->at(iter + 1), iter);
        }
        else if(iter == line_num - 1)
        {
            sum += getGearRatiosInLine(input->at(iter - 1), input->at(iter), "\0", iter);
        }
        else
        {
            sum += getGearRatiosInLine(input->at(iter - 1), input->at(iter), input->at(iter + 1), iter);
        }
    }

    return sum;
}

int main()
{
    FileReader Input("input_03.txt");
    Input.ReadFile();

    vector<string> Input_Ctnt = Input.getFileContent();

    unsigned int PartNumbersSum = 0, GearRatioSum = 0;

    PartNumbersSum = parseLines4PartNumbers(&Input_Ctnt, Input.getLineNum());

    printf("Sum of all part numbers is %d\n", PartNumbersSum);

    GearRatioSum = parseLines4GearRatios(&Input_Ctnt, Input.getLineNum());

    printf("Sum of all gear ratios is %d\n", GearRatioSum);

    return 0;
}
