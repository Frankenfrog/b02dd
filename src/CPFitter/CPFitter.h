// from std
#include "string"
#include "vector"
#include "exception"
#include "typeinfo"

// from Root
#include "TFile.h"

// from RooFit
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include "RooArgSet.h"
#include "RooArgList.h"
#include "RooDataSet.h"
#include "RooUnblindUniform.h"
#include "RooBDecay.h"
#include "RooFitResult.h"
#include "RooLinkedList.h"

// from doosoftware
#include "doocore/io/MsgStream.h"
#include "doocore/io/EasyTuple.h"
#include "doocore/config/EasyConfig.h"
#include "doofit/fitter/easyfit/FitResultPrinter.h"
#include "doofit/plotting/Plot/Plot.h"

// P2VV
#include "P2VV/RooCubicSplineFun.h"
#include "P2VV/RooGaussEfficiencyModel.h"
#include "P2VV/RooEffResAddModel.h"

// local
#include "DecRateCoeff/DecRateCoeff_Bd.h"

class CPFitter{
public:
    CPFitter(doocore::config::EasyConfig config);
    RooFitResult performTimeFit(RooLinkedList fittingArgs = RooLinkedList());
    void readWS();
    void saveWS();
    void timePlot();
protected:
private:
    doocore::config::EasyConfig config_;
    std::vector<std::string> paths_;
    std::vector<int> years_;
    std::vector<int> finalstates_; // 1 D02K3pi D2Kpipi     2 D02K3pi D2KKpi        3 D02Kpi D2Kpipi        4 D02Kpi D2KKpi      5 D02KK D2Kpipi
    std::vector<double> knots_;
    bool useMC_;
    bool doMassFit_;
    bool useTrueTags_;
    bool useOSTagger_;
    bool useSSTagger_;
    bool usePerEventRes_;
    bool readWS_;
    RooArgSet obs_;
    RooWorkspace ws_;
    void buildObservableSet_();
    void readData_();
    void buildFitPDF_();
};

// other
std::vector<int> convertVectorStringToInt(std::vector<std::string> stringVector);
std::vector<double> convertVectorStringToDouble(std::vector<std::string> stringVector);
std::pair<std::vector<std::string>, std::vector<std::string>> convertPairVectorToVectorPair(std::vector<std::pair<std::string, std::string>> pairVector);
