#ifndef __GENESIS__
#define __GENESIS__
#define SR (44100.f)  //sample rate
#define F_PI (3.14159f);
#include "IPlug_include_in_plug_hdr.h"
#include <math.h>
//#include "filter.h"
//#include "Effects.h"

class LP6 {
public:
  LP6() :
  cutoff(0.1),
  resonance(0.0),
  buf0(0.0)
  {
    calculateFeedbackAmount();
  };
  double process(double inputValue);
  inline void set(double newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
  inline void setResonance(double newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
private:
  double cutoff;
  double resonance;
  double feedbackAmount;
  inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance/(1.0 - cutoff); }
  double buf0;
};
class LP12 {
public:
    LP12() :
    cutoff(0.1),
    resonance(0.0),
    buf0(0.0),
    buf1(0.0)
    {
        calculateFeedbackAmount();
    };
    double process(double inputValue);
    inline void set(double newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
    inline void setResonance(double newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
private:
    double cutoff;
    double resonance;
    double feedbackAmount;
    inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance/(1.0 - cutoff); }
    double buf0;
    double buf1;
};
class LP24 {
public:
    LP24() :
    cutoff(0.1),
    resonance(0.0),
    buf0(0.0),
    buf1(0.0),
	buf2(0.0),
    buf3(0.0)
    {
        calculateFeedbackAmount();
    };
    double process(double inputValue);
    inline void set(double newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
    inline void setResonance(double newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
private:
    double cutoff;
    double resonance;
    double feedbackAmount;
    inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance/(1.0 - cutoff); }
    double buf0;
    double buf1;
	double buf2;
	double buf3;
};
class LP48 {
public:
  LP48() :
  cutoff(0.1),
  resonance(0.0),
  buf0(0.0),
  buf1(0.0),
  buf2(0.0),
  buf3(0.0),
  buf4(0.0),
  buf5(0.0),
  buf6(0.0),
  buf7(0.0)
  {
    calculateFeedbackAmount();
  };
  double process(double inputValue);
  inline void set(double newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
  inline void setResonance(double newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
private:
  double cutoff;
  double resonance;
  double feedbackAmount;
  inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance/(1.0 - cutoff); }
  double buf0;
  double buf1;
  double buf2;
  double buf3;
  double buf4;
  double buf5;
  double buf6;
  double buf7;
};
class HP12 {
public:
    HP12() :
    cutoff(0.1),
    resonance(0.0),
    buf0(0.0),
    buf1(0.0)
    {
        calculateFeedbackAmount();
    };
    double process(double inputValue);
    inline void set(double newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
    inline void setResonance(double newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
private:
    double cutoff;
    double resonance;
    double feedbackAmount;
    inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance/(1.0 - cutoff); }
    double buf0;
    double buf1;
};
class HP24 {
public:
    HP24() :
    cutoff(0.1),
    resonance(0.0),
    buf0(0.0),
    buf1(0.0),
	buf2(0.0),
    buf3(0.0)
    {
        calculateFeedbackAmount();
    };
    double process(double inputValue);
    inline void set(double newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
    inline void setResonance(double newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
private:
    double cutoff;
    double resonance;
    double feedbackAmount;
    inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance/(1.0 - cutoff); }
    double buf0;
    double buf1;
	double buf2;
	double buf3;
};
class HP48 {
public:
  HP48() :
  cutoff(0.1),
  resonance(0.0),
  buf0(0.0),
  buf1(0.0),
  buf2(0.0),
  buf3(0.0),
  buf4(0.0),
  buf5(0.0),
  buf6(0.0),
  buf7(0.0)
  {
    calculateFeedbackAmount();
  };
  double process(double inputValue);
  inline void set(double newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
  inline void setResonance(double newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
private:
  double cutoff;
  double resonance;
  double feedbackAmount;
  inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance/(1.0 - cutoff); }
  double buf0;
  double buf1;
  double buf2;
  double buf3;
  double buf4;
  double buf5;
  double buf6;
  double buf7;
};
class Notch {
public:
	Notch() :
		cutoff(0.1),
		resonance(1.0),
		buf0(0.0),
		buf1(0.0),
		buf2(0.0),
		buf3(0.0)
	{
		calculateFeedbackAmount();
	};
	double process(double inputValue);
	inline void set(double newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
	inline void setResonance(double newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
private:
	double cutoff;
	double resonance;
	double feedbackAmount;
	inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance / (1.0 - cutoff); }
	double buf0;
	double buf1;
	double buf2;
	double buf3;

};
class Clipper {
public:
	double process(double inputValue);
private:
	double k;
};
class LFO {
public:
	LFO() :
		out(0.0),
		mPI(2 * acos(0.0)),
		mFrequency(0.00001),
		mPhase(0.0),
		mSampleRate(44100.0) {
		updateIncrement();
	};
	void setFrequency(double Frequency);
	void setSampleRate(double sampleRate);
	void setPhase(double phase);
	double process(double inputValue);
private:
	const double mPI;
	double mFrequency;
	double mPhase;
	double mSampleRate;
	double mPhaseIncrement;
	void updateIncrement();
	double out;
};
class Compressor{
public:
  Compressor():
    peakOutput(0.0),
    peakB0Attack(1.0),
    outputGain(0.0),
    dynamicsAttackTime(0.0),
    dynamicsReleaseTime(0.5),
    dynamicsOutputGain(0.0) {
    set(44100);
  };
  void set(double sampleRate);
  double dynamics(double inputGain);
  double peakFinder(double inputValue);
private:
  double inputAbs;
  double peakfinderB0;
  double peakOutput;
  double fs;
  double peakfinderB0Attack;
  double peakfinderFinderA1;
  double peakfinderB0Release;
  double peakfinderReleaseTime;
  double peakB0Attack;
  double peakfinderA1;
  double outputGain;
  double dynamicsAttackTime;
  double dynamicsB0Attack;
  double dynamicsReleaseTime;
  double dynamicsB0Release;
  double dynamicsOutputGain;
  double dynamicsB0;
  
};
class EnvelopeFollower
{
public:
  EnvelopeFollower():
    envelope(0)
  {
    set(10.0,200.0,44100);
  };
  void set(double attackMs, double releaseMs, int sampleRate);
  void process(double input);
  double sidechain(double input, double sidechainSignal);
  double envelope;
private:
  double temp;
  double attack;
  double release;
};
class Limiter{
public:
  double process(double input);
  void set(double attackMs, double releaseMs, double threshold, int sampleRate);
  EnvelopeFollower ef;
private:
  double th;
  double temp;
};
class Gate{
public:
  Gate():
  releaseTime(0.2),
  sr(44100),
  threshold(0.001),
  outputValue(0.0),
  gain(1.0),
  holdTime(1.0),
  attackTime(0.01){
    set(44100.0);
  };
  double process(double inputValue);
  void set(double sampleRate);
private:
  double releaseTime;
  double sr;
  double release;
  double threshold;
  double outputValue;
  double gain;
  int tick;
  double hold;
  double holdTime;
  double attack;
  double attackTime;
};
class Genesis : public IPlug
{
public:
  Genesis(IPlugInstanceInfo instanceInfo);
  ~Genesis();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double attackTime;
  double attackCoeff;
  double releaseTime;
  double releaseCoeff;
  double envelope=0.0;
  double currentLevel= 50.0;
  double targetLevel;
  double ramp;
  double sr1;
  double sr2;
  double bs1;
  double fq1;
  double fq2;
  double fq3;
  double fq4;
  double fq5;
  double fq6;
  double fq7;
  double fq8;
  double fq9;
  double fq10;
  double fq11;
  double fq12;
  double fq13;
  double fq14;
  double fq15;
  double fq16;
  double mGain;
  double l=0.0;
  double r=0.0;
  double left=0.0;
  double right=0.0;
  double peakOutL=0.0;
  double peakOutR=0.0;
  double peakSum=0.0;
  double gainDb=0.0;
  double gain=0.0;
  double ratio=10.0;
  double thresholdDb=(-12.0);
  double targetGain;
  HP12 filter1;
  LP48 filter2;
  LP24 filter3;
  HP48 filter4;
  HP24 filter5;
  LP24 filter6;
  LP6 filter7;
  LP12 filter8;
  HP12 filter9;
  LP48 filter10;
  LP24 filter11;
  HP48 filter12;
  HP24 filter13;
  LP24 filter14;
  LP6 filter15;
  LP12 filter16;
  Notch filter17;
  Notch filter18;
  HP12 filter19;
  HP12 filter20;
  HP24 filter21;
  HP24 filter22;
  LP12 filter23;
  LP12 filter24;
  LP12 filter25;
  LP12 filter26;
  HP12 filter27;
  HP12 filter28;
  HP24 filter29;
  HP24 filter30;
  LP24 filter31;
  LP24 filter32;
  LFO lfo1;
  LFO lfo2;
  Gate gate1;
  Gate gate2;
  Compressor comp1;
  Compressor comp2;
  //gam::Notch<double> notch1;
  //gam::Notch<double> notch2;
  //gam::FreqShift<double> shifter1;
  //gam::FreqShift<double> shifter2;
  Clipper clipper1;
  Clipper clipper2;
  Clipper clipper3;
  Clipper clipper4;
  Limiter limiter1;
  Limiter limiter2;
  Limiter limiter3;
  Limiter limiter4;
  Limiter limiter5;
  Limiter limiter6;
  EnvelopeFollower sidechain1;
  EnvelopeFollower sidechain2;
  EnvelopeFollower sidechain3;
  EnvelopeFollower sidechain4;
};

#endif
