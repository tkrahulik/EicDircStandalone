#include "EicDircStandaloneGeometry.hh"

EicDircStandaloneGeometry::EicDircStandaloneGeometry(){
  SetDefault();
  CalcDependentParameters();
}

EicDircStandaloneGeometry::~EicDircStandaloneGeometry() {}

void EicDircStandaloneGeometry::SetDefault(){

  world_x = 1.0 * m;
  world_y = 1.0 * m;
  world_z = 5.0 * m;

  bar_x = 1.7 * cm;
  bar_y = 3.5 * cm;
  bar_z = 490. *cm;



  return;

}

void EicDircStandaloneGeometry::CalcDependentParameters() {

  return;

}
