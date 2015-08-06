#include "EicDircStandalonePrimaryGeneratorAction.hh"
#include "EicDircStandalonePrimaryGeneratorMessenger.hh"

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

  //create a messenger for this class
  gunMessenger = new EicDircStandalonePrimaryGeneratorMessenger(this);

  //default kinematic
  //
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("e-");

  particleGun->SetParticleDefinition(particle);
  particleGun->SetParticleTime(0.0*ns);
  //particleGun->SetParticlePosition(G4ThreeVector(0.0*cm,0.0*cm,-1.0*m));
  //particleGun->SetParticleMomentum(G4ThreeVector(0.,0.,10.*GeV));
  particleGun->SetParticlePosition(G4ThreeVector(0.*cm,-50.*cm,10.*cm));
  particleGun->SetParticleMomentum(G4ThreeVector(0., 50.*GeV, -10.*GeV ));
  //particleGun->SetParticleMomentum(G4ThreeVector(0., 10.*GeV, 0.*GeV ));
  //particleGun->SetParticleMomentumDirection(G4ThreeVector(0.0*cm,0.0*cm,-1.0*m));
  //particleGun->SetParticleEnergy(50*KeV);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandalonePrimaryGeneratorAction::~EicDircStandalonePrimaryGeneratorAction()
{
  delete particleGun;
  delete gunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EicDircStandalonePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  particleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EicDircStandalonePrimaryGeneratorAction::SetOptPhotonPolar()
{
  G4double angle = G4UniformRand() * 360.0*deg;
  SetOptPhotonPolar(angle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EicDircStandalonePrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
  if (particleGun->GetParticleDefinition()->GetParticleName() != "opticalphoton")
    {
      G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
        "the particleGun is not an opticalphoton" << G4endl;
      return;
    }

  G4ThreeVector normal (1., 0., 0.);
  G4ThreeVector kphoton = particleGun->GetParticleMomentumDirection();
  G4ThreeVector product = normal.cross(kphoton);
  G4double modul2       = product*product;

  G4ThreeVector e_perpend (0., 0., 1.);
  if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product;
  G4ThreeVector e_paralle    = e_perpend.cross(kphoton);

  G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
  particleGun->SetParticlePolarization(polar);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
