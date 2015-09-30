#ifndef EicDircStandaloneMaterial_h
#define EicDircStandaloneMaterial_h 1
#include "globals.hh"
#include <vector>
#include "G4String.hh"
#include "G4Material.hh"
//#include "G4MaterialTable.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4OpticalSurface.hh"

class EicDircStandaloneMaterial {

public:
  EicDircStandaloneMaterial();
  virtual ~EicDircStandaloneMaterial();

  G4Material* getQuartz() {return Quartz;}

  G4Material* getAir() {return AmbientAir;}
  G4Material* getMirrorQuartz() {return SiO2MirrorQuartz;}

  G4Material* getVacuum() {return Vacuum;}


  G4OpticalSurface* getOpticalMirrorSurface() {return OpticalMirrorSurface;}
  G4OpticalSurface* getOpticalPhotocathodeSurface() {return OpticalPhotocathodeSurface;}

private:
  G4Element* H;
  G4Element* N;
  G4Element* O;
  G4Element* C;
  G4Element* F;
  G4Element* Si;
  G4Material* Q;

  G4Material* Quartz;

  G4Material* Vacuum;
  G4Material* AmbientAir;
  G4Material* SiO2MirrorQuartz;

  G4OpticalSurface* OpticalMirrorSurface;
  G4OpticalSurface* OpticalPhotocathodeSurface;

};

#endif

