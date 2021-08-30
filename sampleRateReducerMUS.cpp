/*

Copyright MUS 2020

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.


*/



#include <lv2plugin.hpp>
#include <math.h>
#include <lv2lib00_MUS/mainMUS.h>

using namespace LV2;

class SampleRateReducerMUS : public Plugin<SampleRateReducerMUS> {
public:

  SampleRateReducerMUS(double rate)
    : Plugin<SampleRateReducerMUS>(6) {

      sh = new SampHold00(0.5);
      ph = new Phasor02();

  }

  void run(uint32_t nframes) {

    float sr = *p(2);

    sr = sr < 1 ? 1 : sr;
    sr = sr > 44100 ? 44100 : sr;

    float sr_scale = *p(3);

    sr_scale = sr_scale < 0 ? 0 : sr_scale;
    sr_scale = sr_scale > 1 ? 1 : sr_scale;

    float sr_tot = sr * sr_scale;

    float mix = *p(4);

    mix = mix < 0 ? 0 : mix;
    mix = mix > 1 ? 1 : mix;

    float rmix = 1.0 - mix;



    float amp = *p(5);

    amp = amp < 0 ? 0 : amp;
    amp = amp > 1 ? 1 : amp;



    ph->setFreq(sr_tot);




    for (uint32_t i = 0; i < nframes; ++i) {

      float in = p(0)[i];

      float reduced = sh->ar(ph->ar(), in);

      float out = (reduced * mix) + (in * rmix);


      p(1)[i] = out * amp;


    }

  }

protected:
SampHold00* sh;
Phasor02* ph;


};

static int _ = SampleRateReducerMUS::register_class("http://musens.pluggar/lv2/lv2pftci/sampleRateReducerMUS");
