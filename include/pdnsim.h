#ifndef __PDNSim_HEADER__
#define __PDNSim_HEADER__


namespace odb {
  class dbDatabase;
}
namespace sta {
  class dbSta;
}

namespace pdnsim {

class PDNSim
{
  public:
    PDNSim();
    ~PDNSim();

    void init();
    void reset();

    void setDb(odb::dbDatabase* odb);
    void setSta(sta::dbSta* dbSta);
    
    void import_vsrc_cfg(const char* vsrc);
    void import_resistance_cfg(const char* res_cfg);

    void analyze_power_grid()

  private:
    odb::dbDatabase* _db;
    sta::dbSta* _sta;
    std::string _vsrc_loc;
    std::string _res_cfg;


};
}

#endif
