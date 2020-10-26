#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "Filtro_DetectorConstruction.hh"
#include "Filtro_ActionInitialization.hh"
#include "Filtro_PhysicsList.hh"

#include "FTFP_BERT.hh"
#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"

#include "G4VisExecutive.hh"

#include "G4UIExecutive.hh"

#include "G4Threading.hh"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ============================================================================

int main(int argc,char** argv) {
    
    srand (time(NULL));
    CLHEP::HepRandom::setTheSeed((int)(rand()*1000000));

// ============================================================================
// Run manager

    G4double RIndex = 1;
    if (argc==2) {
        RIndex = atof(argv [1]);
    }
    if (argc==3) {
        RIndex = atof(argv [2]);
    }

    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(7);
    runManager->SetVerboseLevel(0);

    Filtro_DetectorConstruction* detConstruction = new Filtro_DetectorConstruction(RIndex);
    runManager->SetUserInitialization(detConstruction);



    G4VModularPhysicsList* physicsList = new FTFP_BERT();
    physicsList->ReplacePhysics(new G4EmStandardPhysics_option1());

    G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
    physicsList->RegisterPhysics(opticalPhysics);

    physicsList->SetVerboseLevel(0);
    runManager->SetUserInitialization(physicsList);


    
    Filtro_ActionInitialization* actionInitialization
    = new Filtro_ActionInitialization(detConstruction);

    runManager->SetUserInitialization(actionInitialization);


// visualization manager
    G4VisManager* visManager = new G4VisExecutive;
    visManager->SetVerboseLevel(0);
    visManager->Initialize();

// Initialize G4 kernel
    runManager->Initialize();

// ============================================================================
// User Interface
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    UImanager->SetVerboseLevel(0);

// Define UI session for interactive mode
    if (argc < 3) 
    {
        G4UIExecutive * ui = new G4UIExecutive(argc,argv);
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    } 
    else if (argc == 3) 
    {

        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);

    }

// ============================================================================
// Delete
    delete visManager;
    delete runManager;

    return 0;
}

// ============================================================================
