#include <iostream>
#include <cmath>

#include "globals.hh"

#include "EicDircStandaloneMaterial.hh"

#include "G4Isotope.hh"
#include "G4NistManager.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4UnitsTable.hh"

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4MaterialPropertyVector.hh"


EicDircStandaloneMaterial::EicDircStandaloneMaterial(){

  G4double a; //atomic mass
  G4double z;  //atomic number
  G4double density; //density
  G4double temperature; //temperature
  G4double pressure; //pressure

  G4int nelements;
  G4int natoms;

  //  // Elements
  //  //
  //  H  = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);
  //  N  = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  //  O  = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
  //  C  = new G4Element("Carbon", "C", z=6 , a=12.01*g/mole);
  //  F  = new G4Element("Fluorine", "F", z=9 , a=19.00*g/mole);

  // G4 database on G4Elements
  G4NistManager* manager = G4NistManager::Instance();
  manager->SetVerbose(0);
  //
  // define Elements
  //

  H  = manager->FindOrBuildElement(z=1);
  N  = manager->FindOrBuildElement(z=7);
  O  = manager->FindOrBuildElement(z=8);
  C  = manager->FindOrBuildElement(z=6);
  F  = manager->FindOrBuildElement(z=9);
  Si = manager->FindOrBuildElement(z=14);

  //Vacuum
  //
  density=universe_mean_density;
  a=1.01*g/mole;
  pressure=1.e-19*pascal;
  temperature=0.1*kelvin;

  Vacuum = new G4Material("Galactic",density,nelements=1,kStateGas,temperature,pressure);
  Vacuum->AddElement(H,natoms=1);

  // Air
  //
  AmbientAir = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  AmbientAir->AddElement(N, 70.*perCent);
  AmbientAir->AddElement(O, 30.*perCent);

  const G4int air_nEntries = 32;

  G4double air_PhotonEnergy[air_nEntries] =
    { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
      2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
      2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
      2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
      2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
      3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
      3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
      3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV
    };

  G4double air_RefractiveIndex[air_nEntries] = 
    { 1.00029, 1.00029, 1.00029, 1.00029,
      1.00029, 1.00029, 1.00029, 1.00029,
      1.00029, 1.00029, 1.00029, 1.00029,
      1.00029, 1.00029, 1.00029, 1.00029,
      1.00029, 1.00029, 1.00029, 1.00029,
      1.00029, 1.00029, 1.00029, 1.00029,
      1.00029, 1.00029, 1.00029, 1.00029,
      1.00029, 1.00029, 1.00029, 1.00029
    };

  G4MaterialPropertiesTable* fMPT_air = new G4MaterialPropertiesTable();

  fMPT_air->AddProperty("RINDEX", air_PhotonEnergy, air_RefractiveIndex, air_nEntries )->SetSpline(true);

  AmbientAir->SetMaterialPropertiesTable(fMPT_air);


  //Quartz
  //
  Quartz = new G4Material("Quartz", density=2.200*g/cm3, nelements=2);
  Quartz->AddElement(Si, natoms=1);
  Quartz->AddElement(O, natoms=2);

  const G4int q_nEntries =44;

  /* PhotonEnergy and RefractiveIndex for BaBar Fused Silica (quartz) from
   * J. Cohen-Tanugi et al, 'Optical Properties of the DIRC Fused Silica Cherenkov
   * Radiator', SLAC-PUB-9735, April 2003, arXiv:hep-ex/0305001v1
   */
  G4double q_PhotonEnergy[q_nEntries] =
    { 2.09628*eV, 2.12869*eV, 2.16212*eV, 2.19456*eV,
      2.23224*eV, 2.26903*eV, 2.30478*eV, 2.34402*eV,
      2.38462*eV, 2.42413*eV, 2.46758*eV, 2.51531*eV,
      2.55653*eV, 2.6078*eV,  2.65513*eV, 2.70735*eV,
      2.76165*eV, 2.81479*eV, 2.87531*eV, 2.93848*eV,
      2.99872*eV, 3.06549*eV, 3.1353*eV,  3.20397*eV,
      3.28031*eV, 3.35556*eV, 3.44444*eV, 3.53283*eV,
      3.62026*eV, 3.71803*eV, 3.82122*eV, 3.92372*eV,
      4.03883*eV, 4.16089*eV, 4.29056*eV, 4.42857*eV,
      4.57576*eV, 4.72351*eV, 4.89133*eV, 5.06054*eV,
      5.25365*eV, 5.47485*eV, 5.68773*eV, 5.93283*eV
    };

  /* PhotonEnergy and RefractiveIndex for BaBar Fused Silica (quartz) from
   * J. Cohen-Tanugi et al, 'Optical Properties of the DIRC Fused Silica Cherenkov
   * Radiator', SLAC-PUB-9735, April 2003, arXiv:hep-ex/0305001v1
   */
  G4double q_RefractiveIndex[q_nEntries] = 
    { 1.45728, 1.45730, 1.45732, 1.45735,
      1.45838, 1.45840, 1.45842, 1.45945,
      1.45948, 1.45950, 1.46053, 1.46055,
      1.46057, 1.46160, 1.46163, 1.46266,
      1.46268, 1.46371, 1.46524, 1.46527,
      1.46680, 1.46783, 1.46785, 1.46888,
      1.46991, 1.47094, 1.47198, 1.47401,
      1.47605, 1.47708, 1.47811, 1.48015,
      1.48219, 1.48524, 1.48728, 1.49133,
      1.49438, 1.49843, 1.50249, 1.50755,
      1.51362, 1.51969, 1.52778, 1.53889,
    };

  G4MaterialPropertiesTable* fMPT_q = new G4MaterialPropertiesTable();

  fMPT_q->AddProperty("RINDEX", q_PhotonEnergy, q_RefractiveIndex, q_nEntries )->SetSpline(true);

  Quartz->SetMaterialPropertiesTable(fMPT_q);
  Quartz->SetMaterialPropertiesTable(fMPT_q);

  // done
  //
  return;

}

EicDircStandaloneMaterial::~EicDircStandaloneMaterial(){ }
