#include "EicDircStandalonePrimaryGeneratorAction.hh"

#include "Randomize.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandalonePrimaryGeneratorAction::EicDircStandalonePrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);

  //default kinematic
  //
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("pi-");

  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleTime(0.0*ns);
  particleGun->SetParticlePosition(G4ThreeVector(-15.*cm,0.*cm,0.*cm));
  particleGun->SetParticleMomentum(G4ThreeVector(5.*GeV, 0.*GeV, 0.*GeV ));

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandalonePrimaryGeneratorAction::~EicDircStandalonePrimaryGeneratorAction()
{
  delete particleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EicDircStandalonePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  particleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
