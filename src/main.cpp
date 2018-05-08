#include <iostream>
#include "parser.h"

int main(){
/*leggi metadata
crea match
loop(ogni T){
  leggi eventi_posizione;
  leggi eventi_arbitro(pause e sostituzioni);
  simulateMatch(eventi_posizione,eventi_arbitro);
  stampa_possesso;
}
*/
Parser *p= new Parser();
p->parse_file("game_splitted");
}
