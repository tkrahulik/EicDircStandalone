#ifndef EicDircStandalonePrimaryGeneratorMessenger_h
#define EicDircStandalonePrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class EicDircStandalonePrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/** @TODO Review this class completely
 */
class EicDircStandalonePrimaryGeneratorMessenger: public G4UImessenger
{
public:
  EicDircStandalonePrimaryGeneratorMessenger(EicDircStandalonePrimaryGeneratorAction*);
  ~EicDircStandalonePrimaryGeneratorMessenger();

  void SetNewValue(G4UIcommand*, G4String);

private:
  EicDircStandalonePrimaryGeneratorAction* EicDircStandaloneAction;
  G4UIdirectory*               gunDir;
  G4UIcmdWithADoubleAndUnit*   polarCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

