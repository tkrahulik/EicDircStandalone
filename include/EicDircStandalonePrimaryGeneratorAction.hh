#ifndef EicDircStandalonePrimaryGeneratorAction_h
#define EicDircStandalonePrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class EicDircStandalonePrimaryGeneratorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/** @TODO Review this class completely
 */
class EicDircStandalonePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  EicDircStandalonePrimaryGeneratorAction();
  ~EicDircStandalonePrimaryGeneratorAction();

public:
  void GeneratePrimaries(G4Event*);

  void SetOptPhotonPolar();
  void SetOptPhotonPolar(G4double);

private:
  G4ParticleGun* particleGun;
  EicDircStandalonePrimaryGeneratorMessenger* gunMessenger;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*EicDircStandalonePrimaryGeneratorAction_h*/
