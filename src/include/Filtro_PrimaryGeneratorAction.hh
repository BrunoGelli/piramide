#ifndef Filtro_PrimaryGeneratorAction_h
#define Filtro_PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class Filtro_PrimaryGeneratorMessenger;

// ============================================================================

class Filtro_PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
    
  public:
    Filtro_PrimaryGeneratorAction();
   ~Filtro_PrimaryGeneratorAction();

  public:
    void GeneratePrimaries(G4Event*);

    bool traped;

  private:
    G4ParticleGun* particleGun;
    
};

// ============================================================================

#endif /*Filtro_PrimaryGeneratorAction_h*/
