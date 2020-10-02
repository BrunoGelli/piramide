

    double  Zenith          = 0;                     // initialize the Zenith variable
    double  ZenithSelector  = rand() % 100;          // a random number between 0 and 100
    int     ZenithIndex     = 0;                     // initialize the index for the angle selector     

//  In this for loop the program will check if the random number 
//   has a value between any of the steps of the cumulative probability.
//  If so, the index corresponding to that value is stored in ZenithIndex 
//   and it is used to select the angle.

    for (int i = 1; i < 9; ++i)
    {
        if(AngleProb[i-1] <= ZenithSelector && AngleProb[i] > ZenithSelector)
        {
            Zenith = Angle[i]*3.1415/180; // Zenith receives the angle in radians
            ZenithIndex = i;              // ZenithIndex receive the angle index
            break;
        }
    }

// CALCULATING THE POSITION
//
//  
//

    double theta = rand()*2*3.1415; //random between 0 and 2pi

    double raio  = 100.0;


// //  Here the positions are generated using spherical transformations. 
// //  But all positions are centered in the middle of the simulation. So the following transformations are made;

//     G4ThreeVector position = G4ThreeVector(raio*sin(Zenith)*cos(theta)*m, raio*sin(Zenith)*sin(theta)*m, (raio*cos(Zenith) - 33)*m);
// //  this modification randomize the center of the sphere in a cube of 10 m 
//     position.setX( position.getX() + (G4UniformRand()-0.5) * 20 );
//     position.setY( position.getY() + (G4UniformRand()-0.5) * 20 );
//     position.setZ( position.getZ() + (G4UniformRand()-0.5) * 20 );


//     particleGun->SetParticlePosition(position);

// // to get the particle direction we have only to invert the vector

//     particleGun->SetParticleMomentumDirection(position.operator-()); 

    cout << raio*sin(Zenith)*cos(theta) << " " << raio*sin(Zenith)*sin(theta) << " " << raio*cos(Zenith);

// SELECTING THE ENERGY
//
//
//

    double  Energy          = 0;
    double  EnergySelector  = rand();


    for (int i = 1; i < 16; ++i)
    {
        if (MuonMomentumPDF[i-1][ZenithIndex-1] <= EnergySelector && MuonMomentumPDF[i][ZenithIndex-1] > EnergySelector)
        {
            Energy = MuonMomentum[i];
            break;
        }
    }

    cout << " " << Energy << endl;