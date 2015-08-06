#ifndef EicDircStandaloneSD_h
#define EicDircStandaloneSD_h 1
#include "globals.hh"
#include "G4VSensitiveDetector.hh"
#include "G4ThreeVector.hh"
#include "EicDircStandalonePhotoHit.hh"
class G4Step;
class G4HCofThisEvent;


class EicDircStandaloneSD : public G4VSensitiveDetector
{

public:
  EicDircStandaloneSD(G4String , G4String );
  virtual ~EicDircStandaloneSD();

  void Initialize(G4HCofThisEvent*HCE);
  G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
  G4bool ProcessHits_constStep(const G4Step*aStep, G4TouchableHistory*ROhist);
  void EndOfEvent(G4HCofThisEvent*HCE);
  void clear();
  void DrawAll();
  void PrintAll();

private:
  EicDircStandalonePhotoHitsCollection * PhotoHitCollection;
  //G4int NumberOfSensitiveHpds;
  //G4int NumberOfSensitiveSectorsInHpd;
  //G4int NumberOfSensitivePixelsInSector;
  //std::vector<G4int> HpdSDID;

  G4int HCID;
};



#endif
