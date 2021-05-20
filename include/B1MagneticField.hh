#ifndef B1MagneticField_h
#define B1MagneticField_h 1

#include "G4MagneticField.hh"

/// Magnetic Field class
///

class B1MagneticField : public G4MagneticField
{
public:
  B1MagneticField();
  virtual ~B1MagneticField();
  void GetFieldValue(const double Point[4], double *field) const;
  
private:  
  G4double fieldStrength;
  G4double fieldRadius;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
