#ifndef INOUT_H
#define INOUT_H

void readFromConsole(char*& buffer, int& size);

char* readFromFile(const char* filename, char*& buffer, int& fileSize);

void writeToConsole(const char* buffer, int fileSize);

void writeToFile(const char* filename, const char* buffer, int fileSize);

#endif