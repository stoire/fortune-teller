#ifndef SD_HANDLERS_H
#define SD_HANDLERS_H

#include "Arduino.h"

#include "sd_handler.h"
#include "einstein.h"
#include "helpers_serial.h"

SDHandler::SDHandler(int pino_, 
                             String nome_do_arquivo_) : 
                             n_linhas(0), nome_do_arquivo(nome_do_arquivo_), 
                             pino(pino_) {


    Serial.begin(9600);
    Serial.println(now());                     
    // TO FIX: wait for fortuneteller
    //String msg = "[" + agora() + "]" + "[" + "Log" + n_chars(' ', 7) + "]" + ": " + msg;
    //imprime_em_serial_ln(msg);                
    
    //                                                     ^-- MAX_TAMANHO_EVENTO - tamanho("Log") 
    //                                                         path(MAX_TAMANHO_EVENTO): /lib/midia/definicoes.h
    
    /*
    LoggerSerial logger(Serial);
    Log log_(msg);
    logger.logar(log_);
    */
}

void SDHandler::begin(){
  SD.begin(pino);

  // TO FIX: wait for fortuneteller
  // String init_status = SD.begin(pino) ? SUCESS_OPEN_MSG : FAILED_OPEN_MSG;
  // String tipo = (init_status == SUCESSO_ABRIR) ? "Log" : "ErroR";
  // String log_ = "[" + agora() + "]" + "[" + tipo + n_chars(' ', 10 - tipo.length()) + "]" + ": " + init_status;
  // imprime_em_serial_ln(log_);
}

// Gets and sets
void SDHandler::set_pin(int pin_){
  pin = pin_;
}

void SDHandler::set_filename(String filename_){
  filename = filename_;
}

int SDHandler::get_pino(){
  return pino;
}

String SDHandler::get_filename(){
  return filename;
}

void SDHandler::open(int handle_type){  
    file = SD.open(filename, handle_type);
}

void SDHandler::close(){
    file.close();
}

bool SDHandler::delete_file(){
  bool deleted, exists;
  exists = SD.exists(filename);
  deleted = SD.remove(filename);
    
  return exists && deleted;
}

long int SDHandler::size(){
    if(line_num == 0) {
        open();
        while(file.available()){
          file.read();
          line_num++;
        }
        close();

        return line_num;
    } else return line_num;
}

File& SDHandler::get_file(){
  return file;
}

void SDWriter::mimic(HandlerSD m){
/* Copy other HandlerSD's properties
  Input:
    - [HandlerSD]: HandlerSD copied to be
  Saida:
    - [void]: -
*/

  set_pin(m.get_pin());
  set_filename(m.get_filename());
}

int SDReader::read_int(){
/* Reads an int at a time 
  Input:
    - [void]: -
  Output:
    - [int]: read int
*/
  return file.read();
}

String SDReader::readfile(){
  String content("");

  open(); 
  content += "------\n" ;
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
