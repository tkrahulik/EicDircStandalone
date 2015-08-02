#ifndef EicDircStandaloneDETECTORCONSTRUCTION_H_
#define EicDircStandaloneDETECTORCONSTRUCTION_H_ 1

#include <cmath>
#include <map>
#include <utility>

#include "G4PhysicalConstants.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4String.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"

#include "EicDircStandaloneMaterial.hh"
#include "EicDircStandaloneGeometry.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4PVPlacement;

class EicDircStandaloneDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  EicDircStandaloneDetectorConstruction();
  ~EicDircStandaloneDetectorConstruction();

  G4VPhysicalVolume* Construct();

  EicDircStandaloneMaterial* getDircMaterial() {return  dircMaterial; }
  EicDircStandaloneGeometry* getDircGeometry() {return  dircGeometry; }

protected:

private:

  G4Box* fExperimentalHall_box;
  G4LogicalVolume* fExperimentalHall_log;
  G4VPhysicalVolume* fExperimentalHall_phys;

  EicDircStandaloneMaterial* dircMaterial;
  EicDircStandaloneGeometry* dircGeometry;

};

#endif /* EicDircStandaloneDETECTORCONSTRUCTION_H_ */
