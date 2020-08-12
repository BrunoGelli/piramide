#include "Filtro_SteppingAction.hh"
#include "Filtro_Constantes.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"

#include "G4Run.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"

#include "G4SystemOfUnits.hh"

/* Alteracao 5 5 17 */
#include "G4ios.hh"
#include "G4GeometryTolerance.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4PhysicalConstants.hh"
// */

// Arquivo txt de out put 
#include <fstream>
using namespace std;
//ofstream OutPut_Step(TXT_FILE);

// Conversao de radianos para graus
#define RAD_TO_DEG 180/pi
//================================================================================

Filtro_SteppingAction::Filtro_SteppingAction(
                        Filtro_EventAction *eventAction, Filtro_RunAction* runAction, Filtro_PrimaryGeneratorAction* primaryAction)
    : G4UserSteppingAction (), fEventAction (eventAction), fRunAction (runAction), fPriAction (primaryAction) {
    
    fEventNumber = -1;

}

Filtro_SteppingAction::~Filtro_SteppingAction() { ; }

//================================================================================

void Filtro_SteppingAction::UserSteppingAction (const G4Step* aStep) {
        
    fEventNumber = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    //============================================================================

    
    // Step
    G4Track* track 		= 	aStep->GetTrack();
    G4String particle  	=	track->GetDefinition()->GetParticleName();
    G4String material 	=	track->GetMaterial()->GetName();
    G4double step_x 	= 	aStep->GetTrack()->GetPosition().x();
    G4double step_y 	= 	aStep->GetTrack()->GetPosition().y();
    G4double step_z 	= 	aStep->GetTrack()->GetPosition().z();

    G4double direction_x = aStep->GetDeltaPosition().x();
    G4double direction_y = aStep->GetDeltaPosition().y();
    G4double direction_z = aStep->GetDeltaPosition().z();

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    //PreStep Info
    // G4StepPoint 		*aPrePoint 	= aStep->GetPreStepPoint();
    // G4VPhysicalVolume 	*aPrePV 	= aPrePoint->GetPhysicalVolume();
    // G4String 			PreVolName	= "";

    // if (aPrePV) PreVolName = aPrePV->GetName();
    
    //PostStep Info
    G4StepPoint 		*aPostPoint = aStep->GetPostStepPoint();
    G4VPhysicalVolume 	*aPostPV 	= aPostPoint->GetPhysicalVolume();
    G4String 			PostVolName = "";

    if (aPostPV) PostVolName= aPostPV->GetName();
    
    // energy
	// From the track you can obtain the pointer to the dynamic particle:
	// The dynamic particle class contains e.g. the kinetic energy after the step:
	
    const G4DynamicParticle	*dynParticle 	 = track->GetDynamicParticle();
    G4double 				         kinEnergy 		 = dynParticle->GetKineticEnergy();
    // G4TrackStatus 			     ultimo 			 = aStep->GetTrack()->GetTrackStatus();

    // cout << ultimo << " " << material << " " << PreVolName << " "  << PostVolName << " " << kinEnergy << " " << fEventNumber << endl;

   	if (particle != "mu-")
   	{
		track->SetTrackStatus(fStopAndKill);
   	}

   	if (particle == "mu-" && PostVolName == "detector_LV")
   	{
		analysisManager->FillNtupleIColumn(1,0,fEventNumber);
		analysisManager->FillNtupleDColumn(1,1,step_x/m);
		analysisManager->FillNtupleDColumn(1,2,step_y/m);
		analysisManager->FillNtupleDColumn(1,3,step_z/m);
    analysisManager->FillNtupleDColumn(1,4,track->GetGlobalTime()/ns);
    analysisManager->FillNtupleDColumn(1,5,kinEnergy/GeV);
    analysisManager->FillNtupleDColumn(1,6,direction_x);
    analysisManager->FillNtupleDColumn(1,7,direction_y);
    analysisManager->FillNtupleDColumn(1,8,direction_z);
		analysisManager->AddNtupleRow(1);

		track->SetTrackStatus(fStopAndKill);
   		
   		if ((fEventNumber%1000 == 0 && fEventNumber > 999) ||  fEventNumber == 0)
	   	{
		    cout << "Rodando evento número: "<< fEventNumber << endl;
        // cout << "Rodando evento número: "<< fEventNumber << " " << ultimo << " " << particle << " " << PreVolName << " "  << PostVolName << " " << kinEnergy << " " << fEventNumber << endl;
        cout << "Rodando evento número: "<< fEventNumber << " " << particle << " "  << PostVolName << " " << kinEnergy << endl;
   		}

   	}





}

//================================================================================
