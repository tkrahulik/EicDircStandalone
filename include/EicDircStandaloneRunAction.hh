#ifndef EicDircStandaloneRunAction_h
#define EicDircStandaloneRunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Timer;
class G4Run;

class EicDircStandaloneRunAction : public G4UserRunAction
{
public:
  EicDircStandaloneRunAction();
  ~EicDircStandaloneRunAction();

public:
  void BeginOfRunAction(const G4Run* aRun);
  void EndOfRunAction(const G4Run* aRun);

private:
  G4Timer* timer;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*EicDircStandaloneRunAction_h*/
