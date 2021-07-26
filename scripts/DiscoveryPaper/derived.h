#include "b2dd.h"

class TVector3;
class TLorentzVector;

class discoverypaper : public b2dd {
  public:
    virtual void     Loop();
    TVector3 getthreevector(int i);
    TLorentzVector settrackmasshypo(TVector3 in, float mass);
    float Kppi(int i);
    float Kpip(int i);
    float Kpipi(int i);
    float KKpi(int i);
    float KpiK(int i);
    float pid(int i);
    float ppid(int i);
};
