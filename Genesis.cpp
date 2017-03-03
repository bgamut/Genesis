#include "Genesis.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include <cstddef>
const int kNumPrograms = 1;
const double f1=150.0;
const double f2=300.0;
const double f3=3000.0;
const double f4=300.0;
const double f5=750.0;
const double f6=3000.0;
const double f7=300.0;
const double f8=4500.0;
const double f9=7000.0;

enum EParams
{
  kGain = 0,
  kNumParams
};
enum ELayout
{
  kWidth = 200,
  kHeight = 200,

  kGainX = 0,
  kGainY = 0,
  kKnobFrames = 60
};
double LP6::process(double inputValue) {
  buf0 += cutoff * (inputValue - buf0);
  return buf0;
}
double LP12::process(double inputValue) {
    buf0 += cutoff * (inputValue - buf0);
    buf1 += cutoff * (buf0 - buf1);
            return buf1;
}
double LP24::process(double inputValue) {
    buf0 += cutoff * (inputValue - buf0);
    buf1 += cutoff * (buf0 - buf1);
  buf2 += cutoff * (buf1 - buf2);
	buf3 += cutoff * (buf2 - buf3);	
	return buf3;
		    }
double LP48::process(double inputValue) {
  buf0 += cutoff * (inputValue - buf0);
  buf1 += cutoff * (buf0 - buf1);
  buf2 += cutoff * (buf1 - buf2);
  buf3 += cutoff * (buf2 - buf3);
  buf4 += cutoff * (buf3 - buf4);
  buf5 += cutoff * (buf4 - buf5);
  buf6 += cutoff * (buf5 - buf6);
  buf7 += cutoff * (buf6 - buf7);
  return buf7;
}
double HP12::process(double inputValue) {
    buf0 += cutoff * (inputValue - buf0);
    buf1 += cutoff * (buf0 - buf1);
    return inputValue - buf1;	
    }
double HP24::process(double inputValue) {
    buf0 += cutoff * (inputValue - buf0);
    buf1 += cutoff * (buf0 - buf1);
	buf2 += cutoff * (buf1 - buf2);
  	buf3 += cutoff * (buf2 - buf3);
	  return inputValue - buf3;
    }
double HP48::process(double inputValue) {
  buf0 += cutoff * (inputValue - buf0);
  buf1 += cutoff * (buf0 - buf1);
  buf2 += cutoff * (buf1 - buf2);
  buf3 += cutoff * (buf2 - buf3);
  buf4 += cutoff * (buf3 - buf4);
  buf5 += cutoff * (buf4 - buf5);
  buf6 += cutoff * (buf5 - buf6);
  buf7 += cutoff * (buf6 - buf7);
  return inputValue - buf7;
}
double Notch::process(double inputValue){
	buf0 += cutoff * (inputValue - buf0);
	buf1 += cutoff * (buf0 - buf1);
	buf2 += cutoff * (buf1 - buf2);
	buf3 += cutoff * (buf2 - buf3);
	return inputValue - (buf0 - buf3);
}
void LFO::setFrequency(double frequency) {
	mFrequency = frequency;
	updateIncrement();
}
void LFO::setSampleRate(double sampleRate){
	mSampleRate = sampleRate;
	updateIncrement();
}
void LFO::setPhase(double Phase) {
	mPhase = Phase;
}
void LFO::updateIncrement() {
	mPhaseIncrement = mFrequency * 2 * 3.141952 / mSampleRate;
}
double LFO::process(double inputValue) {
	if (inputValue == 0.0) {
		return 0.0;
	}
	else {
		out = inputValue+sin(mPhase)/16;
		mPhase += mPhaseIncrement;
		if (mPhase >= (2 * 3.141952)) {
			mPhase -= (2 * 3.141952);
			return out;
		}
		else{
			return out;
		}	
	}
}
double Clipper::process(double inputValue){
	//k = inputValue*pow (atan (pow(abs (inputValue), 100)),1/100);
  k=inputValue*pow (atan (pow(abs (inputValue), 5)),1/13);
  //k= atan(pow((inputValue),(5/13)));
	return k; 
}

Genesis::Genesis(IPlugInstanceInfo instanceInfo)
  :	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mGain(1.)
{
  TRACE;

  //arguments are: name, defaultVal, minVal, maxVal, step, label
  GetParam(kGain)->InitDouble("Gain", 50., 0., 100.0, 0.01, "%");
  GetParam(kGain)->SetShape(1.);

  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  pGraphics->AttachPanelBackground(&COLOR_BLACK);

  IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);

  pGraphics->AttachControl(new IKnobMultiControl(this, kGainX, kGainY, kGain, &knob));

  AttachGraphics(pGraphics);

  //MakePreset("preset 1", ... );
  MakeDefaultPreset((char *) "-", kNumPrograms);
}
Genesis::~Genesis() {}
void Genesis::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  // Mutex is already locked for us.
  double* in1 = inputs[0];
  double* in2 = inputs[1];
  double* out1 = outputs[0];
  double* out2 = outputs[1];
  targetLevel = mGain;
  if (targetLevel != currentLevel) {
	  ramp = (targetLevel - currentLevel) / (128 * (nFrames));
	  for (int s = 0; s < nFrames; ++s, ++in1, ++in2, ++out1, ++out2) {
		  *out1 = clipper1.process(4 * filter17.process(filter8.process(filter3.process(filter2.process(filter1.process(((*in1) + (*in2)) / 6))) + (filter7.process(filter6.process(filter5.process(filter4.process(3 * (*in1 - *in2) / 8))))) + (*in1) / 8))*currentLevel);
		  *out2 = clipper2.process(4 * filter18.process(filter16.process(filter11.process(filter10.process(filter9.process(((*in1) + (*in2)) / 6))) + (filter15.process(filter14.process(filter13.process(filter12.process(3 * (*in1 - *in2) / 8))))) + (*in2) / 8))*currentLevel);
		  currentLevel += ramp;
	  }
	  
  }

  else {
	  for (int s = 0; s < nFrames; ++s, ++in1, ++in2, ++out1, ++out2) {
		  *out1 = clipper1.process(4 * filter17.process(filter8.process(filter3.process(filter2.process(filter1.process(((*in1) + (*in2)) / 6))) + (filter7.process(filter6.process(filter5.process(filter4.process(3 * (*in1 - *in2) / 8))))) + (*in1) / 8))*currentLevel);
		  *out2 = clipper2.process(4 * filter18.process(filter16.process(filter11.process(filter10.process(filter9.process(((*in1) + (*in2)) / 6))) + (filter15.process(filter14.process(filter13.process(filter12.process(3 * (*in1 - *in2) / 8))))) + (*in2) / 8))*currentLevel);
	  }
  }

}
void Genesis::Reset()
{
  TRACE;
  sr1=GetSampleRate();
  fq1=2*sin((PI)*f1/sr1);
  fq2=2*sin((PI)*f2/sr1);
  fq3=2*sin((PI)*f3/sr1);
  fq4=2*sin((PI)*f4/sr1);
  fq5=2*sin((PI)*f5/sr1);
  fq6=2*sin((PI)*f6/sr1);
  fq7=2*sin((PI)*f7/sr1);
  fq8=2*sin((PI)*f8/sr1);
  fq9=2*sin((PI)*f9/sr1);
  filter1.set(fq1);
  filter2.set(fq2);
  filter3.set(fq3);
  filter4.set(fq4);
  filter5.set(fq5);
  filter6.set(fq6);
  filter7.set(fq7);
  filter8.set(fq8);
  filter9.set(fq1);
  filter10.set(fq2);
  filter11.set(fq3);
  filter12.set(fq4);
  filter13.set(fq5);
  filter14.set(fq6);
  filter15.set(fq7);
  filter16.set(fq8);
  filter17.set(fq9);
  filter18.set(fq9);
  lfo1.setSampleRate(sr1);
  lfo2.setSampleRate(sr2);
  lfo1.setFrequency(0.5);
  lfo2.setFrequency(0.5);
  lfo1.setPhase(0.0);
  lfo2.setPhase(PI);
  //notch1.zero();
  //notch2.zero();
  //notch1.onDomainChange(sr2 / sr1);
  //notch2.onDomainChange(sr2 / sr1);
  //notch1.freq(7000);
  //notch2.freq(7000);
  //notch1.width(100);
  //notch2.width(100);
  //shifter1.freq(0.01);
  //shifter2.freq(0.02);
  //sr2 = GetSampleRate();
  IMutexLock lock(this);
}
void Genesis::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);

  switch (paramIdx)
  {
    case kGain:
      mGain = GetParam(kGain)->Value() / 100.;
      break;

    default:
      break;
  }
}
