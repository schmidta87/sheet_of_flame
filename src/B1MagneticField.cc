#include "B1MagneticField.hh"
#include "G4SystemOfUnits.hh"

B1MagneticField::B1MagneticField() : G4MagneticField()
{
  fieldStrength=5.*tesla;
  fieldRadius=15.*cm;
}

B1MagneticField::~B1MagneticField(){}

void B1MagneticField::GetFieldValue(const double Point[4], double *field) const
{
  
  G4double x =Point[0];
  G4double y =Point[1];

  field[0]=0.;
  field[2]=0.;

  if (x*x + y*y < fieldRadius*fieldRadius)
    field[1]=fieldStrength;
  else
    field[1]=0.;
}
