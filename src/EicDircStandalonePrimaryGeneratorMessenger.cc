#include "EicDircStandalonePrimaryGeneratorMessenger.hh"

#include "EicDircStandalonePrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandalonePrimaryGeneratorMessenger::EicDircStandalonePrimaryGeneratorMessenger(
                                                                 EicDircStandalonePrimaryGeneratorAction* EicDircStandaloneGun)
 :EicDircStandaloneAction(EicDircStandaloneGun)
{
  gunDir = new G4UIdirectory("/EicDircStandalone/gun/");
  gunDir->SetGuidance("PrimaryGenerator control");

  polarCmd = new G4UIcmdWithADoubleAndUnit("/EicDircStandalone/gun/optPhotonPolar",this);
  polarCmd->SetGuidance("Set linear polarization");
  polarCmd->SetGuidance("  angle w.r.t. (k,n) plane");
  polarCmd->SetParameterName("angle",true);
  polarCmd->SetUnitCategory("Angle");
  polarCmd->SetDefaultValue(-360.0);
  polarCmd->SetDefaultUnit("deg");
  polarCmd->AvailableForStates(G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandalonePrimaryGeneratorMessenger::~EicDircStandalonePrimaryGeneratorMessenger()
{
  delete polarCmd;
  delete gunDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EicDircStandalonePrimaryGeneratorMessenger::SetNewValue(
                                                  G4UIcommand* command, G4String newValue)
{
  if( command == polarCmd ) {
    G4double angle = polarCmd->GetNewDoubleValue(newValue);
    if ( angle == -360.0*deg ) {
      EicDircStandaloneAction->SetOptPhotonPolar();
    } else {
      EicDircStandaloneAction->SetOptPhotonPolar(angle);
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

