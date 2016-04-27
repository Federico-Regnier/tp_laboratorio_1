#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

int getInt(int* input,char message[],char eMessage[], int lowLimit, int hiLimit);
int getFloat(float* input,char message[],char eMessage[], float lowLimit, float hiLimit);
int getChar(char* input,char message[],char eMessage[], char lowLimit, char hiLimit);
int getString(char* input,char message[],char eMessage[], int lowLimit, int hiLimit);
int getLongInt(long int* input,char message[],char eMessage[], long int lowLimit, long int hiLimit);
int getSN(char* input, char message[], char eMessage[]);

#endif // INPUT_H_INCLUDED
