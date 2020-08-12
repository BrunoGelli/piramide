
#include "Filtro_EventAction.hh"
#include "Filtro_RunAction.hh"
#include "Filtro_Constantes.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

//================================================================================

Filtro_EventAction::Filtro_EventAction() {
    

}

//================================================================================

Filtro_EventAction::~Filtro_EventAction() {}

//================================================================================

void Filtro_EventAction::BeginOfEventAction(const G4Event* event) {
    
    nOfReflections = 0;
    nOfDetections = 0;

}

//================================================================================

void Filtro_EventAction::EndOfEventAction(const G4Event* event) {
    


}

//================================================================================
