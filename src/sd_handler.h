#include "Arduino.h"
#include <SD.h>
#include <SPI.h>

#include "const.h"

using namespace std;

class SDHandler {
  public:
    SDHandler(int pin_, String filename_);
    
    void begin();
    void open(int = FILE_READ);
    void close();
    bool delete_file();
    
    void set_pin(int);
    void set_name(String);
    File& getf();
    int get_pin();
    String get_name();

  private:
    long int size();

  protected:
    File file;

  private:
    long int line_num;
    String filename;
    int pin;
};

class SDWriter : public SDHandler {

  public:
    SDWriter() : SDHandler(PINO_CARTAO_SD, RAIZ_SD) {};
    SDWriter(int pin_, String filename_) : SDHandler(pin_, filename) {};

  public:
    template <typename T, size_t N> void write_ln(const T (&msg)[N]){ 
      open(FILE_READ);  
      file.println(msg, N);
      close();
    }
    template <typename T> void write_ln(const T* msg, size_t size){ 
      open(FILE_WRITE);
      file.println(msg, size);
      close();
    }
    template <typename TString> void write_ln(const TString msg){ 
      open(FILE_WRITE);
      file.println(msg);
    }

    template <typename T, size_t N> void write(const T (&msg)[N]){ 
      open(FILE_WRITE);
      file.print(msg, N);
      close();
    }
    template <typename T> void write(const T* msg, size_t size){
      open(FILE_WRITE);
      file.print(msg, size);
      close();  
    }
    template <typename TString> void write(const TString msg){
      write(FILE_WRITE);
      file.print(msg);
      close();
    }

  public:
    void mimic(ManipuladorSD);
};


class SDReader : public SDHandler {
  public:
    SDReader() : SDHandler(DS_PIN, ROOT) {};
    SDReader(int pin_, String filename) : SDHandler(pin_, filename) {};
    
    int readint();
    String readfile();
};
