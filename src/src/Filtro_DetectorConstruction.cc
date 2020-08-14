#include "Filtro_DetectorConstruction.hh"
#include "Filtro_Constantes.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4Torus.hh"

#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VPVParameterisation.hh"
#include "G4PVReplica.hh"
#include "G4AutoDelete.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"

#include "G4SubtractionSolid.hh"
#include "G4VSolid.hh"
#include "G4UnionSolid.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4Navigator.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TransportationManager.hh"

#include <fstream>
using namespace std;


//================================================================================

Filtro_DetectorConstruction::Filtro_DetectorConstruction (G4double RIndex)
: G4VUserDetectorConstruction(), fCheckOverlaps(true), Refr_Index(RIndex) {
  



    // piramide inside
    piramide_x   = 100.0 * m * 0.5;
    piramide_y   = 100.0 * m * 0.5;
    piramide_z   =  60.0 * m * 0.5; 


    // World
    world_x     = 3 * (piramide_x);
    world_y     = 3 * (piramide_y);
    world_z     = 3 * (piramide_z);


    // Base
    base_x       = piramide_x;
    base_y       = piramide_y;
    base_z       = 6 * m * 0.5;   

    // Detector
    detector_x       = 2 * m * 0.5;
    detector_y       = 2 * m * 0.5;
    detector_z       = 2 * m * 0.5;

}

//================================================================================

Filtro_DetectorConstruction::~Filtro_DetectorConstruction (){;}

//================================================================================

G4VPhysicalVolume* Filtro_DetectorConstruction::Construct () {

    // Define materials 
    DefineMaterials();
    
    // Define volumes
    return DefineVolumes();
    
}

//================================================================================

void Filtro_DetectorConstruction::DefineMaterials() {
    

    G4NistManager* nistManager = G4NistManager::Instance();

    nistManager->FindOrBuildMaterial("G4_Galactic");
    nistManager->FindOrBuildMaterial("G4_CONCRETE");


    //Print materials
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
    
}

//================================================================================


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Construction %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

G4VPhysicalVolume* Filtro_DetectorConstruction::DefineVolumes() {
    
//====================== Get Materials ======================

    G4Material* CONCRETE 	= G4Material::GetMaterial("G4_CONCRETE");   
    G4Material* VACUUM 		= G4Material::GetMaterial("G4_Galactic");


//====================== World ======================

    G4Box* 				world_S			=	new G4Box (MUNDO_NOME, world_x, world_y, world_z);
	
    G4LogicalVolume* 	world_LV   		=	new G4LogicalVolume (world_S, VACUUM, MUNDO_NOME);
	
    G4VPhysicalVolume* 	world_PV 		=  	new G4PVPlacement (0, G4ThreeVector (), world_LV, MUNDO_NOME, 0, true, 0, fCheckOverlaps);


//===================== Pirâmide ======================

    G4Trd* 				piramide 		=  	new G4Trd ("piramide", piramide_x, 0, piramide_y, 0, piramide_z);
  //G4Box* 				piramide		=	new G4Box ("piramide", piramide_x,    piramide_y,    piramide_z);

    G4LogicalVolume* 	piramide_LV 	=  	new G4LogicalVolume (piramide, CONCRETE, "piramide_LV");
    
    G4VPhysicalVolume* 	piramide_PV 	=  	new G4PVPlacement (0, G4ThreeVector(), piramide_LV, "piramide_LV", world_LV, true, 0, fCheckOverlaps);


//===================== Base ======================

    G4ThreeVector       pos_base        =       G4ThreeVector(0*cm, 0*cm, -(piramide_z + base_z) );

    G4Box*              base            =   new G4Box("base", base_x, base_y, base_z); 
   
    G4LogicalVolume*    base_LV         =   new G4LogicalVolume (base, CONCRETE, "detector_LV");

    G4VPhysicalVolume*  base_PV         =   new G4PVPlacement (NULL,  pos_base, base_LV, "base_LV",  world_LV, true, 0, fCheckOverlaps);

//===================== Detector ======================

    G4ThreeVector       pos_detector    =       G4ThreeVector(0*cm, 0*cm, 0*cm);//-(piramide_z + base_z + detector_z + 1 * m) );

    G4Box*              detector        =   new G4Box("detector", detector_x, detector_y, detector_z); 
   
    G4LogicalVolume*    detector_LV     =   new G4LogicalVolume (detector, CONCRETE, "detector_LV");

    G4VPhysicalVolume*  detector_PV     =   new G4PVPlacement (NULL,  pos_detector, detector_LV, "detector_LV",  base_LV, true, 0, fCheckOverlaps);


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Visualization Attributes %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    G4VisAttributes* branco = new G4VisAttributes (G4Colour (1.0, 1.0, 1.0, 0.3));
    G4VisAttributes* branco2 = new G4VisAttributes (G4Colour (1.0, 1.0, 1.0, 1));
    G4VisAttributes* branco_vazado = new G4VisAttributes (G4Colour (1.0, 1.0, 1.0, 0.2));
    G4VisAttributes* azul = new G4VisAttributes (G4Colour (0.5, 0.5, 1.0, 0.7));
    G4VisAttributes* azul_vazado = new G4VisAttributes (G4Colour (0.5, 0.5, 1.0, 1));
    G4VisAttributes* verde = new G4VisAttributes (G4Colour (0.5, 1, 0.5, 0.2));
    G4VisAttributes* vermelho = new G4VisAttributes (G4Colour (1, 0, 0, 1));
    G4VisAttributes* transparente = new G4VisAttributes (G4Colour (1, 1, 1, 0));
    G4VisAttributes* preto = new G4VisAttributes (G4Colour (0, 0, 0, 0.2));
    G4VisAttributes* preto_vazado = new G4VisAttributes (G4Colour (0, 0, 0, 1));
    

    branco_vazado->SetForceSolid (false);
    branco->SetForceSolid (true);
    branco2->SetForceSolid (true);
    azul->SetForceSolid (true);
    vermelho->SetForceSolid (true);
    azul_vazado->SetForceSolid (false);
    preto->SetForceSolid(true);
    preto_vazado->SetForceSolid(false);
    verde->SetForceSolid(true);
    transparente->SetForceSolid(false);

    piramide_LV->SetVisAttributes(azul);
    world_LV->SetVisAttributes(transparente);
    detector_LV->SetVisAttributes(branco2);

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% End %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    return world_PV;
    
}

//
//================================================================================

