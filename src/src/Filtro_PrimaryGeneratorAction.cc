#include "Filtro_PrimaryGeneratorAction.hh"
#include "Filtro_Constantes.hh"

#include "lookup.hh"

#include "Randomize.hh"
#include <G4INCLThreeVector.hh>

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "G4SystemOfUnits.hh"
#include <stdlib.h>     /* srand, rand */
#include <stdio.h>

// ============================================================================

Filtro_PrimaryGeneratorAction::Filtro_PrimaryGeneratorAction() {
    
    // default
    G4int n_particle = 1;

    traped  =   true;

    particleGun = new G4ParticleGun(n_particle);
    // particleGun->SetParticleEnergy(15*GeV);
    
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    particleGun->SetParticleDefinition(particleTable->FindParticle("geantino"));
   
}

// ============================================================================

Filtro_PrimaryGeneratorAction::~Filtro_PrimaryGeneratorAction() {
    
  	delete particleGun;
    
}

// ============================================================================

void Filtro_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) { 
    
    // Selecting at whitch zenith angle the muon will be launched
    // This step requires that the number generator follows the 
    // PDF of the muon angular spectrum.
    // 	To achieve this, I used the cummulative probability and
    // 	a uniform probability random number generator. Cheking 
    //  if the UniformRand landed between the cummulative steps
    //  works sorta well (not smoothly, unfortunately)
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();


    if (lookup[anEvent->GetEventID()][7] == -1)
    {
        particleGun->SetParticleDefinition(particleTable->FindParticle("mu-"));
    }
    else
    {
        particleGun->SetParticleDefinition(particleTable->FindParticle("mu+"));
    }   


    G4ThreeVector position  = G4ThreeVector(    lookup[anEvent->GetEventID()][0]*m,
                                                lookup[anEvent->GetEventID()][1]*m,
                                                lookup[anEvent->GetEventID()][2]*m);

    G4ThreeVector direction = G4ThreeVector(    lookup[anEvent->GetEventID()][3],
                                                lookup[anEvent->GetEventID()][4],
                                                lookup[anEvent->GetEventID()][5]);


    particleGun->SetParticleTime(0.*ns);
 
    particleGun->SetParticlePosition(position);

    particleGun->SetParticleMomentumDirection(direction); 

    
    G4double    pp      =   lookup[anEvent->GetEventID()][6];
    G4double    mass    =   particleGun->GetParticleDefinition()->GetPDGMass(); 
    G4double    Ekin    =   sqrt(pp*pp+mass*mass/(1000*1000))-mass/1000; 

    // printf("momentum: %lf GeV/c\n",pp );
    // printf("mass    : %lf MeV/c2\n",mass );
    // printf("Energy  : %lf GeV\n",Ekin );
    // printf("__________\n");
    particleGun->SetParticleEnergy(Ekin * GeV);
    


    particleGun->GeneratePrimaryVertex(anEvent);
    
}

