#include "Filtro_PrimaryGeneratorAction.hh"
#include "Filtro_Constantes.hh"

#include "Randomize.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "G4SystemOfUnits.hh"

// ============================================================================

Filtro_PrimaryGeneratorAction::Filtro_PrimaryGeneratorAction() {
    
    // default
    G4int n_particle = 1;

    traped  =   true;

    particleGun = new G4ParticleGun(n_particle);
    particleGun->SetParticleEnergy(15*GeV);
    
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    particleGun->SetParticleDefinition(particleTable->FindParticle("mu-"));
   
}

// ============================================================================

Filtro_PrimaryGeneratorAction::~Filtro_PrimaryGeneratorAction() {
    
  	delete particleGun;
    
}

// ============================================================================

void Filtro_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) { 
    
    G4double ran_x  = 100.0 * (G4UniformRand()-0.5) * m;
    G4double ran_y  = 100.0 * (G4UniformRand()-0.5) * m;
    G4double pos_z  = 59.0 * m;
    G4double energ  = 20 * GeV;

    particleGun->SetParticleTime(0.*ns);
 
    particleGun->SetParticlePosition(G4ThreeVector(ran_x,ran_y, pos_z));

    particleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, -1)); 

    particleGun->SetParticleEnergy (energ);

    // Gera evento
    particleGun->GeneratePrimaryVertex(anEvent);
    
}



