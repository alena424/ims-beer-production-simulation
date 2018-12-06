/**
 * @project IMS - Simulace pivovaru
 * 
 * @file main.cpp
 * @author Jan Sorm (xsormj00), Alena Tesarova (xtesar36)
 *
 */

#include "mainSmeny.hpp"

Facility stacirna;
unsigned int stacirnaObs = 1;

// zaciname modelovat od pondelni denni smeny
unsigned int denVTydnu = 1;
// zaciname s 23 volnymi tanky
unsigned int volneTanky = 23;
// zaciname s nulovym poctem varek od posledniho cisteni
unsigned int varekOdCisteni = 0;
// na zacatku neni zadny tank rozdelany
bool rozdelanyTank = false;

unsigned int tankyKeStaceni = 0;

unsigned int dobaStatistika = 7 * DEN;

int main() {

   unsigned celkovaDoba = 10 * 365 * DEN;
   std::cout << "Tanku,Pocet smen celkem,Pocet varicich smen nemajici co delat, Pocet stacicich smen nemajici co delat, Pocet stocenych tanku celkem,Pocet tanku 10° piva,Pocet tanku 11° piva, Pocet tanku 12° piva,Pocet tanku specialu" << std::endl;

   for ( int i = 23; i < 60; i++ ) {
      std::cout << i << "," ;

      tankyKeStaceni = 0;
      rozdelanyTank = false;
      varekOdCisteni = 0;
      denVTydnu = 1;
      stacirnaObs = 1;
      volneTanky = i;
      info( "Zacatek simulace" );
      Init( 0, celkovaDoba );
      ( new ClearStat )->Activate();
      ( new Tyden )->Activate();
      ( new Statistika )->Activate( celkovaDoba );
      Run();
      info( "Konec simulace" );
   }
   return 0;
}
