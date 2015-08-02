#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Trap.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Some stuff we may or may not need was here in B1DetectorConstruction.cc??????

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DIRCDetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // No envelope used

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeX = 2000*mm;
  G4double world_sizeY = 2000*mm;
  G4double world_sizeZ = 8000*mm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  //
  //Bar
  //
  G4double bar_hl = 2.45*m   //length (in x) of 4.9 m
  G4double bar_ht = 8.625*mm //thickness (radialy) of 17.25 mm
  G4double bar_hw = 17.5*mm  //width (azimuthaly) of 35 mm
  G4Material* bar_mat = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
  G4double bar_pos_r = 1.0*m //radial distance from IP to bottom inside of bar
  G4ThreeVector bar_pos = G4ThreeVector(0, bar_pos_r + bar_ht, 0);

  G4Box* solidBar =
    new G4Box("Bar",                         //its name
       bar_hl, bar_ht, bar_hw);              //its size

  G4LogicalVolume* logicBar =
    new G4LogicalVolume(solidBar,            //its solid
                        bar_mat,             //its material
                        "Bar");              //its name

  G4VPhysicalVolume* physBar =
    new G4PVPlacement(0,                     //no rotation
                      bar_pos,               //position
                      logicBar,              //its logical volume
                      "Bar",                 //its name
                      logicWorld,            //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

/*
  new G4PVPlacement(0,                       //no rotation
                    bar_pos,                 //at position
                    logicBar,                //its logical volume
                    "Bar",                   //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
*/

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
