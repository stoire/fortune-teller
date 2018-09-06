#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#include "const.h"

using namespace std;

class SDHandler {
  public:
    SDHandler(int pin_);
    
    void begin();
    void open(int = FILE_READ);
    void close();
    bool delf(String);
    
    void set_pin(int);
    void set_name(String);
    File& getf();
    int get_pin();
    String get_name();
    void setfname(String);
    String getfname();

  private:
    long int size();

  protected:
    File file;

  protected:
    long int line_num;
    String filename;
    int pin;
};

class SDWriter : public SDHandler {

  public:
    SDWriter() : SDHandler(SD_PIN) {};
    SDWriter(int pin_) : SDHandler(pin_) {};

  public:
    template <typename T, size_t N> void write_ln(const T (&msg)[N], String to){ 
      filename = to;
      open(FILE_WRITE);
      file.println(msg, N);
      close();
    }
    template <typename T> void write_ln(const T* msg, size_t size, String to){ 
      filename = to;
      open(FILE_WRITE);
      file.println(msg, size);
      close();
    }
    template <typename TString> void write_ln(const TString msg, String to){ 
      filename = to;
      open(FILE_WRITE);
      file.println(msg, to);
      close();
    }

    template <typename T, size_t N> void write(const T (&msg)[N], String to){ 
      filename = to;
      open(FILE_WRITE);
      file.print(msg, N);
      close();
    }
    template <typename T> void write(const T* msg, size_t size, String to){
      filename = to;
      open(FILE_WRITE);
      file.print(msg, size);
      close();  
    }
    template <typename TString> void write(TString msg, String to){
      filename = to;
      //Serial.println(to);
      open(FILE_WRITE);
      file.print(msg);
      close();
    }

  public:
    void mimic(SDHandler);
};


class SDReader : public SDHandler {
  public:
    SDReader() : SDHandler(SD_PIN) {};
    SDReader(int pin_) : SDHandler(pin_) {};
    
    int readint(String);
    String readfile(String);
};
