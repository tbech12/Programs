//Troy Bechtold
//1/22/2020
//CS 122
//Librarys
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//User Defined Functions
string fileName(string fileType); //gets input and output file name
int openFile(string fName, string oFName); //opens file
int englishToMorse(string line, int counter, string oFName); //converts morse to english
int morseToEnglish(string line, int counter, string oFName); //converts english to morse
int morseKey(string letterConvert, string oFile, bool nextLine); //compares with key to convert
int saveConvert(string oFile, string converted, bool nextLine); //saves what the key converts
int englishKey(string oFile, string letterConvert, bool nextLine); //compares with key to convert
int saveUnconvert(string oFile, string unConverted, bool nextLine); //saves what the key converts

//Main Program
int main()
{
  //Data
  string oFileName;
  string iFileName;

  //program FileName
  cout << "Please enter a file that you want to input for the program to read\nThen you will be asked to enter a file you would like to output too.\n" << endl;
  iFileName = fileName("input ");
  oFileName = fileName("output ");

  //waiting for user
  cout << endl;
  cout << "Press the ENTER key to continue..." ;
  cin.ignore (1000, 10);
  
  openFile(iFileName, oFileName);

  cout << "\nPlease check " << oFileName << " to see your converted text." << endl;
}//main

//input and output of emails
string fileName(string fileType)
{
  //data
  string fileName; //file name
  string fileNameExt;// ext on file
  
  //inputfile
  do
  {
    cout << "Please enter " << fileType << "file name: ";
    getline (cin, fileName);
    if (fileName.length() == 0)
    {
      return fileName;
      break;
    }//if 0
    else if (fileName.length() < 5)
    {
      cout << endl << "Invalid file name" << endl << endl;
    }//if less than 5
    else if (fileName.length() >= 5)
    {	
      fileNameExt = fileName.substr(fileName.length()-4, 4);
      if (fileNameExt != ".txt")
      {
        cout << endl << "Invalid file name does not end with .txt" << endl << endl;
      } //if not .txt
      else if (fileNameExt == ".txt")
      {
        return fileName;
        break;
      } // if it has .txt
    }// if greater than 5
  }while (fileName.length() < 5 || fileNameExt != ".txt");
  return 0;
}//email program

//open the file
int openFile(string fName, string oFName)
{
  //data 
  string lineFromFile;  //Lines from the file
  ifstream fin; //Input of file
  int i = 0; //loop counter
  int count = 0; //number of characters 
  bool morse = false;
  bool doneOnce = false;
  int totalCount = 0;
  
  //program
  fin.open(fName);
  if (!fin.good())throw "I/O error";
  while (fin.good())
  {
    getline(fin, lineFromFile);
    count = 0;
    for (i = 0; i <= lineFromFile.length(); i++)
    {
      count++;
      totalCount++;
      if (lineFromFile[i] == '.' || lineFromFile[i] == '-')
      {
        morse = true;
      }//if statement
    }//for loop
    if (morse == false)
    {
      if (doneOnce == false)
      {
        cout << "\nConverting from English to Morse" << endl;
        doneOnce = true;
      }
      morseToEnglish(lineFromFile, count, oFName);
    }//if statement
    else if (morse == true)
    {
      if (doneOnce == false)
      {
        cout << "\nConverting from Morse to English" << endl;
        doneOnce = true;
      }
      englishToMorse(lineFromFile, count, oFName);
    }//else statment
  }//while loop
  cout << "Converted " << totalCount << " characters!" << endl;
  return 0;
}//open file

//english to morse
int englishToMorse(string line, int counter, string oFName)
{
  //data
  //counter = number of character to convert
  //line = the line from file
  int nChar = 0;
  int i = 0;
  int j = 0;
  string code;
  int lastPoint = 0;
  bool nextLine = false;
  
  //program
  for (nChar = 0; nChar <= counter; nChar++)
  {
    if (line[0] == ' ' || line[0] == 0)
    {
      return 0;
    }//if statement
    else if (line[nChar] == ' ' && line[nChar + 1] == ' ' && line[nChar + 2] == ' ')
    {
      for (i = lastPoint; i <= nChar; i++)
      {
        code = code + line[i];
      }
      englishKey(oFName, code, nextLine);
      lastPoint = i + 2;
      code = "";
    }//if statement
    else if(nChar == counter)
    {
      for (i = lastPoint; i <= counter; i++)
      {
        code = code + line[i];
      }//for loop
      nextLine = true;
      englishKey(oFName, code, nextLine);
      saveUnconvert(oFName, "", true);
    }//else if
  }//for loop
  return 0;
}//eng to mor

//morse to english
int morseToEnglish(string line, int counter, string oFName)
{
  //data
  //counter = number of character to convert
  //line = the line from file
  int nChar = 0;
  int asciiCounter = 65;
  int asciiNCounter = 48;
  string letter;
  bool nextLine = false;
  
  //program
  for (nChar = 0; nChar <= counter; nChar++)
  {
    if (line[nChar] != ' ')
    {
    if (nChar == counter)
      {
        nextLine = true;
        saveConvert (oFName, "", nextLine);
        return 0;
      }//not good 
      for (asciiCounter = 65; asciiCounter <= 90; asciiCounter++)
      {
        if(toupper(line[nChar]) == asciiCounter)
        {
          letter = toupper(line[nChar]);
          morseKey(oFName, letter, nextLine);
        }//if statement
        else if (line[nChar] == '1' || line[nChar] == '2' || line[nChar] == '3' || line[nChar] == '4' || line[nChar] == '5' || line[nChar] == '6' || line[nChar] == '7' || line[nChar] == '8' || line[nChar] == '9' || line[nChar] == '0' )
        {
          letter = line[nChar];
          morseKey(oFName, letter, nextLine);
          asciiCounter = 90;
        }//if statement
      }//for loop
    }//if statement
    else if (line[nChar] == ' ')
    {
      letter = line[nChar];
      morseKey(oFName, letter, nextLine);
    }//else if
  }//for loop
  return 0;
}//mor to eng

//Morse to english code
int morseKey(string oFile, string letterConvert, bool nextLine)
{
  //data
  //letterConvert is the current letter being eval
  //oFile is output file
  //nextLine to tell computr to move to next line
  int startPos = 36;
  string englishKey[startPos] = {"",".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..",".----","..---","...--","....-",".....","-....","--...","---..","----.","-----"};
  string morseKey[startPos] = {"","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","0","1","2","3","4","5","6","7","8","9"};
  int i = 0;
  int loop = 0;
  string convertedChar;
  
  //morseCode program
  for (i = 1; i <= 36; i++)
  {
    if (letterConvert == morseKey[i])
    {
      convertedChar = englishKey[i];
      saveConvert(oFile, convertedChar, nextLine);
    }//if state
    else if (letterConvert == " ")
    {
      i = 36;
      saveConvert(oFile, letterConvert, nextLine);
    }//else if statement
  }//for loop
  return 0;
}//key to morse

//Morse to english code
int englishKey(string oFile, string letterConvert, bool nextLine)
{
  //data
  //letterConvert is the current letter being eval
  //oFile is output file
  //nextLine to tell computr to move to next line
  int startPos = 36;
  string englishKey[startPos] = {"",".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..",".----","..---","...--","....-",".....","-....","--...","---..","----.","-----"};
  string morseKey[startPos] = {"","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","0","1","2","3","4","5","6","7","8","9"};
  int i = 0;
  int j = 0;
  int lastStop = 0;
  int loop = 0;
  string convertedChar;
  string letter;
  string temp;
  //cout << "this is the line " << letterConvert << endl;
  
  //morseCode program
  for (i = 0; i <= letterConvert.length(); i++)
  {
    if (letterConvert[i] == ' ')
    {
      for (j = lastStop; j < i; j++)
      {
        letter = letter + letterConvert[j];
      }//for loop
      for (loop = 1; loop < 36; loop++)
      {
        if (letter == englishKey[loop])
        {
          convertedChar = morseKey[loop];
          saveUnconvert(oFile, convertedChar, false);
        }//if state
      }//for loop
      lastStop = i + 1;
      letter = "";
    }//if statement
  }//for loop
  saveUnconvert(oFile, " ", false);
  return 0;
}//key to morse

//saves converted
int saveConvert(string oFile, string converted, bool nextLine)
{
  //data 
  ofstream fout; //output  
  
  //program
  fout.open (oFile.c_str(), ios:: app);
  if(!(fout.good()))throw "I/O error";
  if (nextLine == false)
  {
    fout << converted << " ";
  }
  if (nextLine == true)
  {
    fout << endl;
    nextLine = false;
  }
  fout.close();
  return 0;
}//saves

//saves unconverted
int saveUnconvert(string oFile, string unConverted, bool nextLine)
{
  //data 
  ofstream fout; //output  
  
  //program
  fout.open (oFile.c_str(), ios:: app);
  if(!(fout.good()))throw "I/O error";
  if (nextLine == false)
  {
    fout << unConverted;
  }
  if (nextLine == true)
  {
    fout << endl;
    nextLine = false;
  }
  fout.close();
  return 0;
}//saves
