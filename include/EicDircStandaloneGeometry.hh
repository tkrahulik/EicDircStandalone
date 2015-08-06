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

  G4double GetMirrorX() { return mirror_x; }
  G4double GetMirrorY() { return mirror_y; }
  G4double GetMirrorZ() { return mirror_z; }


  G4double GetMirrorCylinderRadius() {return mirror_cyl_r; }
  G4double GetMirrorCylinderLength() {return mirror_cyl_l; }
  G4double GetMirrorSphereRadius() {return mirror_sphere_r; }
  G4double GetMirrorPositionZ() {return mirror_pos_z; }
  G4double GetMirrorCylinderSphereDistanceZ() {return mirror_cyl_sphere_dist_z; }

private:

  G4double world_x;
  G4double world_y;
  G4double world_z;

  G4double bar_x;
  G4double bar_y;
  G4double bar_z;

  G4double mirror_x;
  G4double mirror_y;
  G4double mirror_z;

  G4double mirror_f;
  G4double mirror_pos_z;
  G4double mirror_cyl_r;
  G4double mirror_cyl_l;
  G4double mirror_sphere_r;
  G4double mirror_cyl_sphere_dist_z;

};

#endif
