#ifndef __GENESIS__
#define __GENESIS__
#define SR (44100.f)  //sample rate
#define F_PI (3.14159f);
#include "IPlug_include_in_plug_hdr.h"
#include <math.h>

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
class Clipper {
public:
	double process(double inputValue);
private:
	double k;
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
  double random1;
  double random2;
  double sr;
  double fq1;
  double fq2;
  double fq3;
  double fq4;
  double fq5;
  double fq6;
  double fq7;
  double fq8;
  double mGain;
  HP12 filter1;
  LP24 filter2;
  LP24 filter3;
  HP24 filter4;
  HP24 filter5;
  LP24 filter6;
  LP12 filter7;
  LP12 filter8;
  HP12 filter9;
  LP24 filter10;
  LP24 filter11;
  HP24 filter12;
  HP24 filter13;
  LP24 filter14;
  LP12 filter15;
  LP12 filter16;
  Clipper clipper1;
  Clipper clipper2;
};

#endif
