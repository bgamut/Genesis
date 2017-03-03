#ifndef __GENESIS__
#define __GENESIS__
#define SR (44100.f)  //sample rate
#define MAX_FRAME_LENGTH 8192
#include "queue.h"

//#define F_PI (3.14159f);
#include "IPlug_include_in_plug_hdr.h"
#include <math.h>
//#include "filter.h"
//#include "Effects.h"
//#include "smbPitchShift.h"
//#include "simple_pitchshift.h"
#include <string.h>
#include <stdio.h>

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
class Shifter {
public:
	Shifter() :
		pitchShift(0.000000001),
		BufferSize(128),
		osamp(4),
		sampleRate(44100)
	{
	
	};
	inline void setBufferSize(int newBufferLengthFrames) { BufferLengthFrames = newBufferLengthFrames; }
	inline void setSampleRate(double newSampleRate) { sampleRate = newSampleRate; }
	inline void setPitchShift(double newPitchShift) { pitchShift = newPitchShift; }
	double pitchShift;	
	double sampleRate;
private:
	
	int BufferLengthFrames;
	int BufferSize;
	int osamp;

	double* in;
	double* out;
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
class Genesis : public IPlug
{
public:
  Genesis(IPlugInstanceInfo instanceInfo);
  ~Genesis();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  double currentLevel= 50.0;
  double targetLevel;
  double ramp;
  double sr1;
  double sr2=GetSampleRate();
  double fq1;
  double fq2;
  double fq3;
  double fq4;
  double fq5;
  double fq6;
  double fq7;
  double fq8;
  double fq9;
  double mGain;
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
  LFO lfo1;
  LFO lfo2;
  //gam::Notch<double> notch1;
  //gam::Notch<double> notch2;
  //gam::FreqShift<double> shifter1;
  //gam::FreqShift<double> shifter2;
  Clipper clipper1;
  Clipper clipper2;
  Shifter shifter1;
  Shifter shifter2;
};

#endif
