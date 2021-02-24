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

    

    double  Zenith          = 0;                     // initialize the Zenith variable
    double  ZenithSelector  = rand() % 100;          // a random number between 0 and 100
    int     ZenithIndex     = 0;                     // initialize the index for the angle selector     

    for (int i = 1; i < 9; ++i)
    {
        if(AngleProb[i-1] <= ZenithSelector && AngleProb[i] > ZenithSelector)
        {
            Zenith = Angle[i]*3.1415/180; // Zenith receives the angle in radians
            ZenithIndex = i;              // ZenithIndex receive the angle index
            break;
        }
    }

    double theta = rand()%100;
    theta = (theta/100) *2*3.1415; //random between 0 and 2pi

    double raio  = 100.0;

    double xrand = 0;//rand() % 30000 - 15000;
    double yrand = 0;//rand() % 30000 - 15000;
    double zrand = -33;//rand() % 30000 - 15000;

    double mod =    pow(raio*sin(Zenith)*cos(theta) , 2) + 
                    pow(raio*sin(Zenith)*sin(theta) , 2) + 
                    pow(raio*cos(Zenith)            , 2);

    mod = pow(mod,0.5);


    double  Energy = 0;


    while(Energy < 16)
    {
        double  EnergySelector  = (rand() % 10000000) ;

        for (int i = 1; i < 16; ++i)
        {
            if (MuonMomentumPDF[i-1][ZenithIndex-1] <= EnergySelector/10000000 && MuonMomentumPDF[i][ZenithIndex-1] > EnergySelector/10000000)
            {
                Energy = MuonMomentum[i];
                break;
            }
        }
       
    }


    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();

    G4int evento = anEvent->GetEventID();


    double chargeSelector = rand() % 10000;

    chargeSelector = chargeSelector / 100;

    if (chargeSelector > 45.45)
    {
        particleGun->SetParticleDefinition(particleTable->FindParticle("mu-"));
    }
    else 
    {
        particleGun->SetParticleDefinition(particleTable->FindParticle("mu+"));
    }



    G4ThreeVector position  = G4ThreeVector(    (raio*sin(Zenith)*cos(theta)  + xrand)*m,
                                                (raio*sin(Zenith)*sin(theta)  + yrand)*m,
                                                (raio*cos(Zenith)             + zrand)*m);

    G4ThreeVector direction = G4ThreeVector(    -(raio*sin(Zenith)*cos(theta) )/mod,
                                                -(raio*sin(Zenith)*sin(theta) )/mod,
                                                -(raio*cos(Zenith)            )/mod);


    particleGun->SetParticleTime(0.*ns);
 
    particleGun->SetParticlePosition(position);

    particleGun->SetParticleMomentumDirection(direction); 

    
    G4double    pp      =   Energy;
    G4double    mass    =   particleGun->GetParticleDefinition()->GetPDGMass(); 
    G4double    Ekin    =   sqrt(pp*pp+mass*mass/(1000*1000))-mass/1000; 

    particleGun->SetParticleEnergy(Ekin * GeV);
    


    particleGun->GeneratePrimaryVertex(anEvent);
    
}

