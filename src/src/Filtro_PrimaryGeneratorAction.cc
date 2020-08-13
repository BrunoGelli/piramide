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
    
    G4double ran_x  = 1.0 * (G4UniformRand()-0.5) * m;
    G4double ran_y  = 1.0 * (G4UniformRand()-0.5) * m;
    G4double pos_z  = -10.0 * m;
    G4double energ  = 20 * GeV;

    particleGun->SetParticleTime(0.*ns);
 
    particleGun->SetParticlePosition(G4ThreeVector(ran_x,ran_y, pos_z));

    particleGun->SetParticleMomentumDirection(G4ThreeVector(0, 0, -1)); 

    particleGun->SetParticleEnergy (energ);

    // Gera evento
    particleGun->GeneratePrimaryVertex(anEvent);
    
}



/* here I will discuss about the muon generator

Discribed in this paper (Development of the ADAMO detector: test with cosmic rays at different zenith angles [L. Bonechi])
the muon flux depending on the zenith is as described bellow. 

0 < a < 10 (degrees) x1e0

    1.30208e-1, 3.47828e+1
    2.10518e-1, 3.27829e+1
    3.40362e-1, 3.50707e+1
    5.50291e-1, 3.73027e+1
    8.89700e-1, 2.85760e+1
    1.43845e+0, 2.11475e+1
    2.29303e+0, 1.26457e+1
    3.70732e+0, 6.81819e+0
    5.90983e+0, 3.16466e+0
    9.55489e+0, 1.20786e+0
    1.54482e+1, 4.30229e-1
    2.49763e+1, 1.24555e-1
    4.03812e+1, 3.28861e-2
    6.43715e+1, 7.68420e-3
    1.04075e+2, 2.31881e-3

10 < a < 20 (degrees) x1e-1

    1.32061e-1, 4.59417e+0
    2.13514e-1, 3.47511e+0
    3.45206e-1, 3.23407e+0
    5.50291e-1, 3.03026e+0
    8.77216e-1, 2.48998e+0
    1.41827e+0, 1.70981e+0
    2.29303e+0, 1.10329e+0
    3.70732e+0, 5.94863e-1
    5.99393e+0, 2.57110e-1
    9.69087e+0, 1.14242e-1
    1.54482e+1, 3.98982e-2
    2.46259e+1, 1.16162e-2
    4.04632e+1, 3.54766e-3
    6.43715e+1, 9.08611e-4
    1.04075e+2, 5.70321e-4

20 < a < 30 (degrees) x1e-2

    1.32061e-1, 4.26542e-1
    2.13514e-1, 3.75611e-1
    3.45206e-1, 2.84118e-1
    5.42570e-1, 3.27490e-1
    8.77216e-1, 2.36022e-1
    1.41827e+0, 1.92629e-1
    2.29303e+0, 1.16804e-1
    3.70732e+0, 6.42965e-2
    5.99393e+0, 3.23523e-2
    9.55489e+0, 1.10352e-2
    1.54482e+1, 5.04940e-3
    2.46259e+1, 1.27302e-3
    3.98146e+1, 4.85874e-4
    6.43715e+1, 1.31274e-4
    1.04075e+2, 7.96005e-5

30 < a < 40 (degrees) x1e-3

    1.04122e+2, 1.15821e-6
    6.41235e+1, 7.99219e-6
    4.01337e+1, 4.02116e-5
    2.47162e+1, 8.48254e-5
    1.54694e+1, 3.64405e-4
    9.37411e+0, 1.14095e-3
    5.86707e+0, 2.40714e-3
    3.67208e+0, 4.69270e-3
    2.29828e+0, 7.81117e-3
    1.41539e+0, 1.20126e-2
    8.85867e-1, 1.51646e-2
    5.54447e-1, 1.99151e-2
    3.41455e-1, 1.76160e-2
    2.13710e-1, 2.13769e-2
    1.29503e-1, 2.30352e-2

40 < a < 50 (degrees) x1e-4

    1.31613e-1, 1.23835e-3
    2.13710e-1, 1.34575e-3
    3.41455e-1, 1.20016e-3
    5.54447e-1, 1.02901e-3
    8.85867e-1, 9.93133e-4
    1.43845e+0, 7.86814e-4
    2.29828e+0, 5.75921e-4
    3.73190e+0, 3.46043e-4
    5.96264e+0, 1.77504e-4
    9.68200e+0, 7.47418e-5
    1.57214e+1, 3.02525e-5
    2.47162e+1, 9.65825e-6
    4.01337e+1, 3.20858e-6
    6.51681e+1, 1.29870e-6
    1.04122e+2, 3.14492e-7

50 < a < 60 (degrees) x1e-5

    1.31613e-1, 8.77678e-5
    2.13710e-1, 4.32830e-5
    3.47017e-1, 5.29551e-5
    5.54447e-1, 5.11089e-5
    8.85867e-1, 4.38142e-5
    1.41539e+0, 4.22867e-5
    2.29828e+0, 2.74969e-5
    3.73190e+0, 2.09408e-5
    5.96264e+0, 1.03256e-5
    9.68200e+0, 4.89486e-6
    1.54694e+1, 2.06080e-6
    2.51189e+1, 8.34129e-7
    4.07874e+1, 2.56055e-7
    6.51681e+1, 6.45043e-8
    1.05818e+2, 1.82968e-8

60 < a < 70 (degrees) x1e-6 

    1.31613e-1, 4.90777e-6
    2.10284e-1, 4.73667e-6
    3.35982e-1, 3.90332e-6
    5.63478e-1, 2.34597e-6
    8.85867e-1, 2.54871e-6
    1.46188e+0, 2.36523e-6
    2.29828e+0, 1.59952e-6
    3.67208e+0, 1.17080e-6
    5.96264e+0, 7.03474e-7
    9.68200e+0, 3.90572e-7
    1.54694e+1, 2.00346e-7
    2.51189e+1, 5.91185e-8
    4.01337e+1, 2.39255e-8
    6.51681e+1, 1.00743e-8
    1.04122e+2, 6.05233e-9

70 < a < 80 (degrees) x1e-7

    1.29503e-1, 2.43726e-7
    2.13710e-1, 2.26180e-7
    3.41455e-1, 1.72228e-7
    5.54447e-1, 1.07653e-7
    8.57696e-1, 6.21520e-8
    1.43845e+0, 6.49440e-8
    2.33572e+0, 6.26885e-8
    3.61322e+0, 4.23882e-8
    6.05977e+0, 3.63533e-8
    9.52681e+0, 2.01779e-8
    1.57214e+1, 1.31225e-8
    2.51189e+1, 6.21988e-9
    3.94904e+1, 1.98572e-9
    6.51681e+1, 8.69943e-10
    1.05818e+2, 2.46761e-10

