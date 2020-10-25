#ifndef Filtro_DetectorConstruction_h
#define Filtro_DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;

class Filtro_DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    Filtro_DetectorConstruction(G4double RIndex);
    virtual ~Filtro_DetectorConstruction();
    
 

  public:
    virtual G4VPhysicalVolume* Construct();

  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    // World
    G4double world_x, world_y, world_z;
    
    // piramide in
    G4double piramide_x, piramide_y, piramide_z;

    // detector
    G4double detector_x, detector_y, detector_z;

    // detector
    G4double base_x, base_y, base_z;

    // fim da linha
    G4double fim_x, fim_y, fim_z;

    G4bool  fCheckOverlaps; 
    G4double Refr_Index;


   
};

#endif /*Filtro_DetectorConstruction_h*/
