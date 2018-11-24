/**
 * @project IMS - Simulace pivovaru
 *
 * @file main.hpp
 * @author Jan Sorm (xsormj00), Alena Tesarova (xtesar36)
 *
 */

#include <iostream>
#include <simlib.h>
#include <string>

// casove konstanty
#define DEN 86400
#define HODINA 3600

// pocet tanku
#define TANKY 23

// globalni promenne pro zjisteni, jaky je den v tydnu
extern unsigned int denVTydnu;
// globalni promenna pro pocet volnych tanku
extern unsigned int volneTanky;
// globalni promenna pro znaceni pocet varek od posledniho cisteni
extern unsigned int varekOdCisteni;
// globalni promenna pro zjisteni, zda mame nejaky tank poloplny
extern bool rozdelanyTank;

extern unsigned int tankyKeStaceni;

extern Facility stacirna;

extern unsigned int stacirnaObs;

void info( const char *retezec ) {
   // pokud debugujeme, tak vypisovat, jinak ne
   if ( 1 ) {
      std::cerr << static_cast<int>(Time) << ": " << retezec << std::endl;
   }
}

/**
 * Proces zajistujici staceni piva.
 */
class Staceni: public Process {
   void Behavior() {
      if ( tankyKeStaceni ) {
         info( "Jdeme stacet tank." );
         tankyKeStaceni--;
         Wait( 6 * HODINA );
         info( "Umyjeme tank." );
         Wait( 4 * HODINA );
         info( "Vracime tank mezi volne." );
         volneTanky++;
      }
   }
};

/**
 * Proces simulujici kvaseni piva.
 */
class Kvaseni: public Process {
   void Behavior() {
      double r = Random();
      int dobaKvaseni;
      if ( r <= 0.7 ) {
         info( "Kvasime 11°." );
         dobaKvaseni = 30;
      } else if ( r > 0.7 && r <= 0.83 ) {
         info( "Kvasime 12°." );
         dobaKvaseni = 45;
      } else if ( r > 0.83 && r <= 0.93 ) {
         info( "Kvasime 13°." );
         dobaKvaseni = 60;
      } else {
         info( "Kvasime 16°." );
         dobaKvaseni = 90;
      }
      Wait( dobaKvaseni * DEN );
      tankyKeStaceni++; 
   }
};

/**
 * Proces simulujici proces vareni piva.
 */
class Vareni: public Process {
   void Behavior() {
      if ( varekOdCisteni == 10 ) {
         info( "Jdeme cistit tanky na vareni." );
         varekOdCisteni = 0;
      } else {
         if ( rozdelanyTank ) {
            info( "Jdeme dodelat varku do rozdelaneho tanku" );
            varekOdCisteni++;
            rozdelanyTank = false;
            ( new Kvaseni )->Activate( Time + 12 * HODINA );
         } else if ( volneTanky > 0 ) {
            info( "Jdeme vytvorit varku do noveho volneho tanku" );
            volneTanky--;
            varekOdCisteni++;
            rozdelanyTank = true;
         }
      }
   }
};

/**
 * Proces znacici, zda je vikend nebo ne.
 */
class Tyden: public Process {
   void Behavior() {
      // tento proces bezi porad dokola
      while ( 1 ) {
         if ( denVTydnu < 6 ) {
            info( "Prisla denni smena na staceni a vareni." );
            ( new Vareni )->Activate();
            ( new Staceni )->Activate();
            Wait( 12 * HODINA );
            info( "Prisla nocni smena na vareni." );
            ( new Vareni )->Activate();
            Wait( 12 * HODINA );
            denVTydnu++;
         } else {
            info( "Prisla sobotni smena na vareni." );
            ( new Vareni )->Activate();
            Wait( DEN );
            denVTydnu++;
            info( "Prisla nedelni smena na vareni." );
            ( new Vareni )->Activate();
            Wait( DEN );
            denVTydnu = 1;
         }
      }
   }
};
