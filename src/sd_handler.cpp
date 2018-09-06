#ifndef SD_HANDLERS_H
#define SD_HANDLERS_H

#include "sd_handler.h"
#include "converters/fundamental.h"

SDHandler::SDHandler(int pin_) : 
                     line_num(0), 
                     pin(pin_) {

    // TO FIX: wait for courier
    //String msg = "[" + agora() + "]" + "[" + "Log" + n_chars(' ', 7) + "]" + ": " + msg;
    //imprime_em_serial_ln(msg);                
        
    /*
    LoggerSerial logger(Serial);
    Log log_(msg);
    logger.logar(log_);
    */
}

void SDHandler::begin(){
  SD.begin(pin);

  // TO FIX: wait for courier
  // String init_status = SD.begin(pino) ? SUCESS_OPEN_MSG : FAILED_OPEN_MSG;
  // String tipo = (init_status == SUCESSO_ABRIR) ? "Log" : "ErroR";
  // String log_ = "[" + agora() + "]" + "[" + tipo + n_chars(' ', 10 - tipo.length()) + "]" + ": " + init_status;
  // imprime_em_serial_ln(log_);
}

// Gets and sets
void SDHandler::set_pin(int pin_){
  pin = pin_;
}

void SDHandler::setfname(String filename_){
  filename = filename_;
}

int SDHandler::get_pin(){
  return pin;
}

String SDHandler::getfname(){
  return filename;
}

void SDHandler::open(int handle_type){  
    file = SD.open(filename, handle_type);
}

void SDHandler::close(){
    file.close();
}

bool SDHandler::delf(String fname){
  bool deleted, exists;
  exists = SD.exists(fname);
  deleted = SD.remove(fname);
    
  return exists && deleted;
}

long int SDHandler::size(){
    open();
    while(file.available()){
      file.read();
      line_num++;
    }
    close();

    return line_num;
}

File& SDHandler::getf(){
  return file;
}

void SDWriter::mimic(SDHandler m){
/* Copy other HandlerSD's properties
  Input:
    - [HandlerSD]: HandlerSD copied to be
  Saida:
    - [void]: -
*/

  set_pin(m.get_pin());
  setfname(m.getfname());
}

int SDReader::readint(String from){
/* Reads an int at a time 
  Input:
    - [void]: -
  Output:
    - [int]: read int
*/
  filename = from;
  return file.read();
}

String SDReader::readfile(String from){
  String content("");

  filename = from;

  open();
  content += "------\n";
  content += file.name();
  content += ":\n";

  while(file.available()) {
    char s = file.read();
    content+=s;
  }

  content += "\n------\n" ;
  close();

  return content;
}

#endif
