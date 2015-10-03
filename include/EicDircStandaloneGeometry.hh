#ifndef EicDircStandaloneDETECTORGEOMETRY_H_
#define EicDircStandaloneDETECTORGEOMETRY_H_ 1

#include "globals.hh"

class EicDircStandaloneGeometry
{
public:
  EicDircStandaloneGeometry();
  ~EicDircStandaloneGeometry();

  void SetDefault();
  void CalcDependentParameters();

  G4double GetWorldX() { return world_x; }
  G4double GetWorldY() { return world_y; }
  G4double GetWorldZ() { return world_z; }

  G4double GetBarX() { return bar_x; }
  G4double GetBarY() { return bar_y; }
  G4double GetBarZ() { return bar_z; }

private:

  G4double world_x;
  G4double world_y;
  G4double world_z;

  G4double bar_x;
  G4double bar_y;
  G4double bar_z;

};

#endif
