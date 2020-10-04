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



	G4double	Zenith 			= 0;
    G4double	ZenithSelector 	= G4UniformRand() * 100;
    G4int		ZenithIndex 	= 0;

    printf("%d  - %lf\n",anEvent->GetEventID(),  lookup[anEvent->GetEventID()][0]);
    
    for (int i = 1; i < 9; ++i)
    {
    	if(AngleProb[i-1] <= ZenithSelector && AngleProb[i] > ZenithSelector)
    	{
    		Zenith = Angle[i]*3.1415/180;
    		ZenithIndex = i;
    		break;
    	}
    }


	G4double theta = G4UniformRand()*2*3.1415;

    G4double raio  = 100.0;


    // G4ThreeVector DetecPos = G4ThreeVector(0 * m, 0 * m, -33 * m);

    G4ThreeVector position = G4ThreeVector(raio*sin(Zenith)*cos(theta)*m, raio*sin(Zenith)*sin(theta)*m, (raio*cos(Zenith) - 33)*m);


    particleGun->SetParticleTime(0.*ns);
 
    particleGun->SetParticlePosition(position);

	position.setZ(position.getZ() + 33*m);

    particleGun->SetParticleMomentumDirection(position.operator-()); 




	G4double	Energy 			= 0;
    G4double	EnergySelector 	= G4UniformRand();

    // printf("The ZenithIndex is %d | ", ZenithIndex);

    for (int i = 1; i < 16; ++i)
    {
    	if (MuonMomentumPDF[i-1][ZenithIndex] <= EnergySelector && MuonMomentumPDF[i][ZenithIndex] > EnergySelector)
    	{
    		Energy = MuonMomentum[i];
    		break;
    	}
    }


    particleGun->SetParticleEnergy (Energy * GeV);

    // printf("The geantino energy is %lf GeV\n", Energy);

    particleGun->GeneratePrimaryVertex(anEvent);
    
}

