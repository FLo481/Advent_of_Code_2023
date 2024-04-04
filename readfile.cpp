/*
 * Lib for reading text file and process content
 */

#include <fstream>
#include <iostream>
#include <string.h>
#include "readfile.hpp"

FileReader::FileReader(const char* filename) : m_linenum(0)
{
    strcpy(m_filename, filename);
}

FileReader::~FileReader()
{
    m_lines.clear();
}

void
FileReader::PrintContents()
{
    vector<string>::iterator it;
    unsigned int line_num = 0;

    for(it = m_lines.begin(); it != m_lines.end(); it++, line_num++)
        printf("%d: %s\n", line_num + 1, m_lines[line_num].c_str());
}

void
FileReader::ReadFile()
{
    ifstream file(m_filename);
    string buffer;

    if(file.is_open())
        printf("Reading file %s ...\n", m_filename);
    else
        printf("ERROR: Cannot open file %s\n", m_filename);

    while(getline(file, buffer))
    {
        m_lines.push_back(buffer);
        m_linenum++;
    }

    file.close();
}

const string&
FileReader::getLine(unsigned int line_num) const
{
    return m_lines[line_num];
}

const vector<string>&
FileReader::getFileContent() const
{
    return m_lines;
}
