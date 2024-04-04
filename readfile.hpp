/*
 * Lib for reading text file and process content
 */

#ifndef READFILE_HPP_
#define READFILE_HPP_

#include <vector>
#include <string>

using namespace std;

class FileReader
{
public:
    FileReader(const char* filename);
    ~FileReader();

    void ReadFile();
    void PrintContents();

    const string& getLine(unsigned int line_num) const;
    const vector<string>& getFileContent() const;

    unsigned int getLineNum()
    {
        return m_linenum;
    }

private:
    char           m_filename[50];
    unsigned int   m_linenum;
    FILE          *p_file;
    vector<string> m_lines;
};

#endif // READFILE_HPP_
