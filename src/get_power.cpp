/*
BSD 3-Clause License

Copyright (c) 2020, The Regents of the University of Minnesota

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "get_power.h"
#include "util.h"
#include <iostream>
#include <tcl.h>

using namespace sta;
using namespace std;


//! Function for power per instance calculation

/*!
     \param libName Timing libraries for OpenSTA
     \return A vector of pairs which has instance name and its corresponding total power
   */

std::vector<pair<string, double>> PowerInst::executePowerPerInst(
    sta::dbSta* sta)
{
  cout << "\n" << endl;
  cout << "INFO: Executing STA for Power" << endl;
  cout << "INFO: Execute STA" << endl;
  cout << "INFO: Files for STA" << endl;
  // STA object create
  _sta = sta;

  std::vector<pair<string, double>> power_report;

  sta::Network* network = _sta->network();
  sta::Power*   power   = _sta->power();
  PowerResult   total, sequential, combinational, macro, pad;
  power->power(corner,
               total,
               sequential,
               combinational,
               macro,
               pad);  // TODO called for preamble
  LeafInstanceIterator* inst_iter = network->leafInstanceIterator();
  PowerResult           total_calc;
  total_calc.clear();
  while (inst_iter->hasNext()) {
    Instance*    inst = inst_iter->next();
    LibertyCell* cell = network->libertyCell(inst);
    if (cell) {
      PowerResult inst_power;
      power->power(inst, corner, inst_power);
      total_calc.incr(inst_power);
      power_report.push_back(
          make_pair(string(network->name(inst)), inst_power.total()));
      // cout << string(network->name(inst)) << inst_power.total() << endl;
    }
  }
  delete inst_iter;

  // cout <<"Total power:" << total.total() << endl;
  // cout <<"Total power calculated:" << total_calc.total() << endl;
  return power_report;
}

//void PowerInst::UpdateTimingSta()
//{
 // _sta->updateTiming(true);
//}
