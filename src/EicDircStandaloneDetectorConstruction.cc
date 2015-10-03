#include "EicDircStandaloneDetectorConstruction.hh"
#include "EicDircStandaloneSD.hh"

#include "globals.hh"
#include "G4ProductionCuts.hh"
#include "G4Tubs.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"

#include "G4NistManager.hh"

#include "G4Cons.hh"
#include "G4DisplacedSolid.hh"
#include "G4ExtrudedSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"

#include <cassert>
#include <iostream>
#include <sstream>
using namespace std;

EicDircStandaloneDetectorConstruction::EicDircStandaloneDetectorConstruction()
{
  _world_box = NULL;
  _world_log = NULL;
  _world_phys = NULL;

  _dircMaterial = NULL;
  _dircGeometry = NULL;
}


EicDircStandaloneDetectorConstruction::~EicDircStandaloneDetectorConstruction()
{

}


G4VPhysicalVolume* EicDircStandaloneDetectorConstruction::Construct()
{
  _dircMaterial = new EicDircStandaloneMaterial();
  _dircGeometry = new EicDircStandaloneGeometry();

  // The World
  //
  _world_box = new G4Box("World",
			 0.5 * getDircGeometry()->GetWorldX(),
			 0.5 * getDircGeometry()->GetWorldY(),
			 0.5 * getDircGeometry()->GetWorldZ()
			 );

  _world_log = new G4LogicalVolume(_world_box,
				   getDircMaterial()->getAir(),
				   "World",
				   0,
				   0,
				   0
				   );

  _world_phys = new G4PVPlacement(0,
				  G4ThreeVector(),
				  _world_log,
				  "World",
				  0,
				  false,
				  0
				  );

  // The Quartz Bar
  //
  G4Box* bar_box = new G4Box("Bar",
			     0.5 * getDircGeometry()->GetBarX(),
			     0.5 * getDircGeometry()->GetBarY(),
			     0.5 * getDircGeometry()->GetBarZ()
			     );

  G4LogicalVolume* bar_log = new G4LogicalVolume(bar_box,
						 getDircMaterial()->getQuartz(),
						 "Bar", 0,0,0);

  //  G4VPhysicalVolume* bar_phys = 
  new G4PVPlacement(0,
		    G4ThreeVector(),
		    bar_log,
		    "Bar",
		    _world_log,
		    false,
		    0
		    );


  // Create volume for photosensor
  //
  G4double photosensor_thickness = 1.0*cm;

  G4Box* photosensor_solid = new G4Box("Photosensor",
				 0.5 * getDircGeometry()->GetBarX(),
				 0.5 * getDircGeometry()->GetBarY(),
				 0.5 * photosensor_thickness
				 );

  G4LogicalVolume* photosensor_log = new G4LogicalVolume(photosensor_solid,
							 getDircMaterial()->getQuartz(),
							 "Photosensor", 0,0,0);
  
  //  G4VPhysicalVolume* photosensor_phys = 
  new G4PVPlacement(0,
		    G4ThreeVector( 0,
				   0,
				   0.5 * getDircGeometry()->GetBarZ() + 0.5 * photosensor_thickness ),
		    photosensor_log,
		    "Photosensor",
		    _world_log,
		    false,
		    0
		    );

  // Make photosensor sensitive Detector
  //
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4String photoSDname = "/EicDircStandaloneDet/photoSD";
  G4String photoHitColname="PhotoHitsCollection";

  EicDircStandaloneSD* photoSD = new EicDircStandaloneSD( photoSDname, photoHitColname );

  SDman->AddNewDetector( photoSD );

  // always return the physical World
  //

  return _world_phys;

}
