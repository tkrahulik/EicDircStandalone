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

  EicDircStandaloneMaterial* getDircMaterial() {return  _dircMaterial; }
  EicDircStandaloneGeometry* getDircGeometry() {return  _dircGeometry; }

protected:

private:

  G4Box* _world_box;
  G4LogicalVolume* _world_log;
  G4VPhysicalVolume* _world_phys;

  EicDircStandaloneMaterial* _dircMaterial;
  EicDircStandaloneGeometry* _dircGeometry;

};

#endif /* EicDircStandaloneDETECTORCONSTRUCTION_H_ */
