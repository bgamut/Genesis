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
const double f10=40.0;
const double f11=105;
const double f12=750;
const double f13=3000;
const double f14=133.1;
const double f15=275.0;
const double f16=12000.0;
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
double toDB (double inputValue){
  //return 20.0 * ((inputValue) > 0.00001 ? log10f(inputValue) : -6.3);
  return 20.0*log10f(inputValue);
}
double toVolume(double dB){
  return powf(10.0, dB);
}
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
  k=inputValue*pow (atan (pow(fabs (inputValue), 5)),1/13);
  //k= atan(pow((inputValue),(5/13)));
  return k;
}

double Compressor::peakFinder(double inputValue){
  inputAbs = fabs(inputValue);
  if(inputAbs>peakOutput){
    peakfinderB0=peakfinderB0Attack;
  }
  else{
    peakfinderB0=peakfinderB0Release;
  }
  peakOutput+=peakfinderB0*(inputAbs-peakOutput);
  return peakOutput;
}
void Compressor::set(double sampleRate){
  fs=sampleRate;
  peakOutput=0.0;
  peakB0Attack=1.0;
  peakfinderA1=exp(-1.0/(peakfinderReleaseTime*fs));
  peakfinderB0Release=1.0-peakfinderA1;
  outputGain=0.0;
  dynamicsAttackTime=0.0;
  dynamicsB0Attack= 1.0-exp(-1.0/(dynamicsAttackTime*fs));
  dynamicsReleaseTime=0.5;
  dynamicsB0Release=1.0-exp(-1.0/(dynamicsReleaseTime*fs));
  dynamicsOutputGain=0.0;
}
double Compressor::dynamics(double inputGain){
  if(inputGain<dynamicsOutputGain){
    dynamicsB0=dynamicsB0Attack;
  }
  else{
    dynamicsB0=dynamicsB0Release;
  }
  dynamicsOutputGain += dynamicsB0*(inputGain-dynamicsOutputGain);
  return dynamicsOutputGain;
}
void Gate::set(double sampleRate){
  sr=sampleRate;
  releaseTime=0.2;
  attackTime=0.00;
  threshold=0.001;
  release=1.0-exp(-1.0/(releaseTime*sr));
  hold=holdTime*sr;
  //attack=1.0-exp(-1.0/(attackTime*sr));
  attack=1.0-exp(-1.0/1.0);
}
double Gate::process(double inputValue){
  if(tick>int(hold)){
    if(threshold>(inputValue*inputValue)){
      gain*=release;
    }
    else{
      tick=0;
      gain*=attack;
    }
  }
  else{
    tick+=1;
    gain=1.0;
  }
  outputValue=inputValue*gain;
  return inputValue;
}
void EnvelopeFollower::set(double attackMs, double releaseMs, int sampleRate){
  attack=pow( 0.01, 1.0 / ( attackMs * sampleRate * 0.001 ) );
  release=pow( 0.01, 1.0 / ( releaseMs * sampleRate * 0.001 ) );
}
void EnvelopeFollower::process(double input){
  temp=fabs(input);
  if(temp>envelope)
    envelope=attack*(envelope-temp)+temp;
  else
    envelope=release*(envelope-temp)+temp;
}
void Limiter::set(double attackMs, double releaseMs, double threshold, int sampleRate){
  ef.envelope=0.0;
  ef.set(attackMs, releaseMs, sampleRate);
  th=threshold;
}
double Limiter::process(double input){
  temp = input;
  ef.process(temp);
  if(ef.envelope>th){
    return input*(th/ef.envelope);
  }
  else{
    return input;
  }
}

Genesis::Genesis(IPlugInstanceInfo instanceInfo)
:	IPLUG_CTOR(kNumParams, kNumPrograms, instanceInfo), mGain(1.)
{
  TRACE;
  
  //arguments are: name, defaultVal, minVal, maxVal, step, label
  GetParam(kGain)->InitDouble("Gain", 50., 0., 100.0, 0.1, "%");
  GetParam(kGain)->SetShape(1.);
  
  IGraphics* pGraphics = MakeGraphics(this, kWidth, kHeight);
  pGraphics->AttachPanelBackground(&COLOR_BLACK);
  
  IBitmap knob = pGraphics->LoadIBitmap(KNOB_ID, KNOB_FN, kKnobFrames);
  
  pGraphics->AttachControl(new IKnobMultiControl(this, kGainX, kGainY, kGain, &knob));
  
  AttachGraphics(pGraphics);
  
  //MakePreset("preset 1", ... );
  MakeDefaultPreset((char *) "-", kNumPrograms);
  if (GetAPI() == kAPIVST2) // for VST2 we name individual outputs
  {
    SetInputLabel(0, "L process");
    SetInputLabel(1, "R process");
    SetInputLabel(2, "L raw");
    SetInputLabel(3, "R raw");
    SetOutputLabel(0, "mixed L");
    SetOutputLabel(1, "mixed R");
  }
  else // for AU and VST3 we name buses
  {
    SetInputBusLabel(0, "process");
    SetInputBusLabel(1, "raw");
    SetOutputBusLabel(0, "output");
  }

}
Genesis::~Genesis() {}
void Genesis::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  // Mutex is already locked for us.
  double* in1 = inputs[0];
  double* in2 = inputs[1];
  double* in3 = inputs[2];
  double* in4 = inputs[3];
  double* out1 = outputs[0];
  double* out2 = outputs[1];
  targetLevel = mGain;
  envelope=0.0;
  if (targetLevel != currentLevel) {
    ramp = (targetLevel - currentLevel) / (4 * (nFrames));
    for (int s = 0; s < nFrames; ++s, ++in1, ++in2,++in3,++in4, ++out1, ++out2) {
      l = 3.0*gate1.process(filter31.process(filter29.process(*in1*currentLevel)));
      r = 3.0*gate2.process(filter32.process(filter30.process(*in2*currentLevel)));
      left =limiter3.process(limiter1.process((*in3*2.0)+7*filter27.process(filter25.process(filter23.process(filter21.process(12 * filter19.process(filter17.process(filter8.process(filter3.process(filter2.process(filter1.process(((l) + (r)) / 8))) + (filter7.process(filter6.process(filter5.process(filter4.process(3 * (l - r) / 8))))) + (l) / 7)))))))));
      right = limiter4.process(limiter2.process((*in4*2.0)+7*filter28.process(filter26.process(filter24.process(filter22.process(12 * filter20.process(filter18.process(filter16.process(filter11.process(filter10.process(filter9.process(((l) + (r)) / 8))) + (filter15.process(filter14.process(filter13.process(filter12.process(3 * (l - r) / 8))))) + (r) /7)))))))));
      
      *out1=clipper3.process(clipper1.process((left)))/2.1;
      *out2=clipper4.process(clipper2.process((right)))/2.1;
      currentLevel += ramp;
    }
    
  }
  
  else {
    for (int s = 0; s < nFrames; ++s, ++in1, ++in2,++in3,++in4, ++out1, ++out2) {
      l = 3.0*filter31.process(filter29.process(gate1.process(*in1*currentLevel)));
      r = 3.0*filter32.process(filter30.process(gate2.process(*in2*currentLevel)));
      left =limiter3.process(limiter1.process((*in3*2.0)+7*filter27.process(filter25.process(filter23.process(filter21.process(12 * filter19.process(filter17.process(filter8.process(filter3.process(filter2.process(filter1.process(((l) + (r)) / 8))) + (filter7.process(filter6.process(filter5.process(filter4.process(3 * (l - r) / 8))))) + (l) / 7)))))))));
      right = limiter4.process(limiter2.process((*in4*2.0)+7*filter28.process(filter26.process(filter24.process(filter22.process(12 * filter20.process(filter18.process(filter16.process(filter11.process(filter10.process(filter9.process(((l) + (r)) / 8))) + (filter15.process(filter14.process(filter13.process(filter12.process(3 * (l - r) / 8))))) + (r) /7)))))))));
      
      *out1=clipper3.process(clipper1.process((left)))/2.1;
      *out2=clipper4.process(clipper2.process((right)))/2.1;
    }
  }
  
}
void Genesis::Reset()
{
  TRACE;
  gain=1.0;
  sr1=GetSampleRate();
  bs1=GetBlockSize();
  fq1=2*sin((PI)*f1/sr1);
  fq2=2*sin((PI)*f2/sr1);
  fq3=2*sin((PI)*f3/sr1);
  fq4=2*sin((PI)*f4/sr1);
  fq5=2*sin((PI)*f5/sr1);
  fq6=2*sin((PI)*f6/sr1);
  fq7=2*sin((PI)*f7/sr1);
  fq8=2*sin((PI)*f8/sr1);
  fq9=2*sin((PI)*f9/sr1);
  fq10=2*sin((PI)*f10/sr1);
  fq11=2*sin((PI)*f11/sr1);
  fq12=2*sin((PI)*f12/sr1);
  fq13=2*sin((PI)*f13/sr1);
  fq14=2*sin((PI)*f14/sr1);
  fq15=2*sin((PI)*f15/sr1);
  fq16=2*sin((PI)*f16/sr1);
  l=0.0;
  r=0.0;
  left=0.0;
  right=0.0;
  peakOutL=0.0;
  peakOutR=0.0;
  peakSum=0.0;
  gainDb=0.0;
  gain=0.0;
  ratio=10.0;
  thresholdDb=(-12.0);
  envelope=0.0;
  gain=1.0;
  attackCoeff=1.0-exp(-1/(attackTime*sr1));
  releaseCoeff=1.0-exp(-1/(releaseTime*sr1));
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
  filter19.set(fq10);
  filter20.set(fq10);
  filter21.set(fq11);
  filter22.set(fq11);
  filter23.set(fq12);
  filter24.set(fq12);
  filter25.set(fq13);
  filter26.set(fq13);
  filter27.set(fq14);
  filter28.set(fq14);
  filter29.set(fq15);
  filter30.set(fq15);
  filter31.set(fq16);
  filter32.set(fq16);
  lfo1.setSampleRate(sr1);
  lfo2.setSampleRate(sr2);
  lfo1.setFrequency(0.5);
  lfo2.setFrequency(0.5);
  lfo1.setPhase(0.0);
  lfo2.setPhase(PI);
  gate1.set(sr1);
  gate2.set(sr1);
  comp1.set(sr1);
  comp2.set(sr1);
  limiter1.set(10.0,500.0,0.5,sr1);
  limiter2.set(10.0,500.0,0.5,sr1);
  limiter3.set(0.03,500.0,1.0,sr1);
  limiter4.set(0.03,500.0,1.0,sr1);
  limiter5.set(0.03,500.0,0.25,sr1);
  limiter6.set(0.03,500.0,0.25,sr1);
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
