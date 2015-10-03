#ifndef EicDircStandalonePrimaryGeneratorAction_h
#define EicDircStandalonePrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EicDircStandalonePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  EicDircStandalonePrimaryGeneratorAction();
  ~EicDircStandalonePrimaryGeneratorAction();

public:
  void GeneratePrimaries(G4Event*);

private:
  G4ParticleGun* particleGun;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*EicDircStandalonePrimaryGeneratorAction_h*/
