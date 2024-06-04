#ifndef INOUT_H
#define INOUT_H

void readFromConsole(int* number);

int readFromFile(const char* filename);

void writeToConsole(const int number);

int writeToFile(const char* filename, const int number);

#endif